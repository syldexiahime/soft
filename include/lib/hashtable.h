#ifndef _SOFT_HASHTABLE_H
#define _SOFT_HASHTABLE_H

struct ht_item {
	void * key;
	void * value;
};

typedef struct hashtable {
	struct ht_item * items;
	size_t length;
	size_t capacity;
	uint64_t (* hashfunc) (const char * key);
} hashtable_t;

// fnv1a
static inline uint64_t ht_default_hashfunc (const char * key)
{
	uint64_t hash = 14695981039346656037UL;

	for (const char * p = key; *p; p++) {
		hash ^= (uint64_t)(unsigned char)(*p);
		hash *= 1099511628211UL;
	}

	return hash;
}

struct ht_create_args {
	size_t capacity;
	uint64_t (* hashfunc) (const char * key);
};

#define ht_create(...) ht_create((struct ht_create_args){__VA_ARGS__});
static struct hashtable * (ht_create) (struct ht_create_args args)
{
	size_t capacity = args.capacity ? args.capacity : 32;

	struct hashtable * table = malloc(sizeof(struct hashtable));

	table->hashfunc = args.hashfunc ? args.hashfunc : ht_default_hashfunc;

	if (table == NULL)
		return NULL;

	table->length = 0;
	table->capacity = capacity;

	table->items = calloc(table->capacity, sizeof(struct ht_item));

	if (table->items == NULL) {
		sfree(table);

		return NULL;
	}

	return table;
}

static void ht_destroy (struct hashtable * table)
{
	for (size_t i = 0; i < table->capacity; i++) {
		if (table->items[i].key != NULL)
			free((void *) table->items[i].key);
	}

	free(table->items);
	free(table);
}

struct ht_locate_res { bool found; size_t index; };

static inline struct ht_locate_res ht_locate (struct ht_item * items, size_t capacity,
		const char * key, uint64_t (* hashfunc) (const char * key))
{
	uint64_t hash = hashfunc(key);
	size_t index = (size_t)(hash & (uint64_t)(capacity - 1));

	while (items[index].key != NULL) {
		if (strcmp(key, items[index].key) == 0)
			return (struct ht_locate_res){ .found = true, .index = index };

		index++;

		if (index >= capacity)
			index = 0;
	}

	return (struct ht_locate_res){ .found = false, .index = index };
}

static inline bool ht_expand (struct hashtable * table)
{
	size_t ncapacity = table->capacity * 2;

	struct ht_item * nitems = calloc(ncapacity, sizeof(struct ht_item));

	if (nitems == NULL)
		return false;

	for (size_t i = 0; i < table->capacity; i++) {
		struct ht_item item = table->items[i];

		if (item.key != NULL) {
			struct ht_locate_res res = ht_locate(nitems, ncapacity,
				item.key, table->hashfunc);
		}
	}

	free(table->items);
	table->items = nitems;
	table->capacity = ncapacity;

	return true;
}

static inline bool ht_contains (struct hashtable * table, const char * key)
{
	struct ht_locate_res res = ht_locate(table->items, table->capacity,
		key, table->hashfunc);

	return res.found;
}

static inline void * ht_get (struct hashtable * table, const char * key)
{
	struct ht_locate_res res = ht_locate(table->items, table->capacity,
		key, table->hashfunc);

	if (!res.found)
		return NULL;

	return table->items[res.index].value;
}

static const bool ht_set (struct hashtable * table, const char * key, void * value)
{
	assert(value != NULL);

	if (value == NULL)
		return false;

	if (table->length >= table->capacity / 2) {
		if (!ht_expand(table))
			return NULL;
	}

	struct ht_locate_res res = ht_locate(table->items, table->capacity,
		key, table->hashfunc);

	if (res.found)
		return false;

	key = strdup(key);

	if (key == NULL)
		return false;

	table->length++;

	table->items[res.index].key = (char *) key;
	table->items[res.index].value = value;

	return key;
}


struct ht_delete_args {
	struct hashtable * table;
	bool free_values;
};

static const bool ht_delete (struct hashtable * table, const char * key)
{
	struct ht_locate_res res = ht_locate(table->items, table->capacity,
		key, table->hashfunc);

	if (!res.found)
		return false;

	table->length--;

	free(table->items[res.index].key);

	table->items[res.index].key = NULL;
	table->items[res.index].value = NULL;

	return true;
}

static inline size_t ht_length (struct hashtable * table)
{
	return table->length;
}

#endif // _SOFT_HASHTABLE_H
