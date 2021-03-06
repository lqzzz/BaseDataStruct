#include "Vector.h"
#define INIT_LEN 4
#define BINARY_SEARCH_FLAG 16
#define SWAP(v1,v2) do {\
	void* temp = v1; \
	v1 = v2;\
	v2 = temp;\
}while(0)

static __inline int32_t default_comp(int* v1, int* v2) {
	int i1 = *v1;
	int i2 = *v2;
	if (i1 > i2)
		return 1;
	else if (i1 < i2)
		return -1;
	else return 0;
}

static __inline int32_t linear_search(Vector* v, void* key,int32_t(*comp)(void*, void*)) {	
	size_t length_ = v->usedsize_;
	void** vector_ = v->vector_;
	for (size_t i = 0; i < length_; i++){
		if (comp(vector_[i], key) == 0)
			return i;
	}
	return -1;
}

static int32_t binary_search(Vector * v,void* key,int32_t(*comp_)(void*, void*)){
	void **v_ = v->vector_;
	int32_t lo = 0, hi = v->usedsize_;
	while (hi > lo) {
		int mi = (lo + hi) >> 1;
		if ((comp_(key, v_[mi]) == -1))
			hi = mi;
		else 
			lo = mi + 1;
	}
	return --lo;
}

Vector * vector_create_len(int len){
	Vector *v = mem_calloc(1,sizeof(Vector)); 
	v->vector_ = mem_calloc(1,sizeof(size_t)*len);
	v->freesize_ = len;
	return v;
}

Vector * vector_create(){
	return vector_create_len(INIT_LEN);
}

int32_t vector_init_v(Vector * dest, Vector * vsrc){
	size_t usedsize_ = vsrc->usedsize_;
	size_t freesize_ = vsrc->freesize_;
	size_t size_ = usedsize_ + freesize_;
	VECTOR_INIT(dest, size_);
	memset(dest, 0, sizeof(Vector));
	if (vsrc->dup_ == NULL)
		dest->vector_ = memcpy(dest->vector_, vsrc->vector_, usedsize_ * sizeof(size_t));
	dest->usedsize_ = usedsize_;
	dest->freesize_ = freesize_;
	return 0;
}

int32_t vector_insert(size_t index, Vector * v,void* value){
	if (v->freesize_ == 0)
		VECTOR_GROW(v, v->usedsize_ << 1);
	if (v->vector_[index] == NULL)
		v->vector_[index] = value;
	else return -1;
	v->usedsize_++;
	v->freesize_--;
	return 0;
}

void * vector_get_val(Vector * v, int index){
	return v->vector_[index];
}

Vector * vector_filter(Vector * v){

	return NULL;
}

//Vector * vector_distinct(Vector * v){
//	if (!VectorGetUsedSize(v))
//		return NULL;
//	Vector *v_ = vector_create();
//	v_->dup_ = v->dup_;
//	v_->free_ = v->free_;
//	v_->comp_ = v->comp_;
//	VectorIter *iter_ = vector_get_begin(v);
//	v_ = push_back(v_, vector_next(iter_));
//	void* key_ = vector_next(iter_);
//	while (key_) {
//		
//	}
//	return NULL;
//}

int32_t vector_copy(Vector * v,Vector* vsrc){

	return 0;
}

//void vector_clear(Vector * v){
//	size_t len = v->usedsize_;
//	if (v->free_)
//		for (size_t i = 0; i < len; ++i)
//			v->free_(v->vector_[i]);
//	else
//		for (size_t i = 0; i < len; ++i)
//			mem_free(v->vector_[i]);
//}
//
//void vector_destruct(Vector* v) {
//	mem_free(v->vector_);
//}
//
//void vector_release(Vector *v){
//	vector_clear(v);
//	vector_destruct(v);
//	mem_free(v);
//}

VectorIter* vector_get_begin(Vector* v){
	VectorIter *iter_;
	if (!(iter_ = mem_alloc(sizeof(VectorIter))))
		return NULL;
	iter_->value_ = &v->vector_[0];
	iter_->index_ = 0;
	return iter_;
}

VectorIter* vector_get_end(Vector* v) {
	VectorIter *iter_;
	if (!(iter_ = mem_alloc(sizeof(VectorIter))))
		return NULL;
	iter_->index_ = v->usedsize_;
	return iter_;
}
	
Vector* vector_value_copy(Vector * vsrc){
	size_t usedsize_ = vsrc->usedsize_;
	size_t freesize_ = vsrc->freesize_;
	size_t size_ = usedsize_ + freesize_;
	Vector* v_ = vector_create_len(size_);
	//if (vsrc->dup_ == NULL) {
	//	for (int i = 0; i < size_; i++){
	//		if (vsrc->vector_[i])
	//			void* data_;
	//	}
	//	memcpy(v_->vector_, vsrc->vector_, usedsize_ * sizeof(size_t));
	//}
	v_->usedsize_ = usedsize_;
	v_->freesize_ = freesize_ ;
	return v_;
}

void insert_sort(Vector *v) {

}

void quicksort(Vector* vsrc, int l, int u) {
	int i, m;
	void** v = vsrc->vector_;
	if (l >= u) return;
	m = l;
	for (i = l + 1; i <= u; i++)
		if (vsrc->comp_(v[u], v[l]) < 0)
			SWAP(v[i], v[l]);
	SWAP(v[l], v[m]);
	quicksort(vsrc, l, m - 1);
	quicksort(vsrc, m + 1, u);
}

inline void vector_sort(Vector * v){
	quicksort(v, 0, v->usedsize_ - 1);
}

inline int32_t vector_search(Vector * v,void* key,int32_t(*comp)(void*, void*)){
	if (comp == NULL)
		comp = default_comp;
	return v->usedsize_ >= BINARY_SEARCH_FLAG ? binary_search(v, key, comp) : linear_search(v, key, comp);
}

int32_t vector_exist(Vector * v, void * key,int32_t(*comp)(void*,void*)){
	//int index_ = vector_search(v, key, comp);
	//if()
	//return ;
}

void vector_release_iter(VectorIter * iter){
	mem_free(iter);
}

int32_t vector_eq_iter(VectorIter *begin, VectorIter *end){
	return begin->index_ == end->index_ ? 1 : 0;
}

void* vector_next(VectorIter * iter){
	iter->index_++;
	return *iter->value_++;
}


/*Vector *v = VectorCreate();
str *str1 = str_new("str1");
str *str2 = str_new("str2");
str *str3 = str_new("str3");
str *str4 = str_new("str4");
v->dup = str_dup;
v->free = str_free;
v->match = str_compare;
v = PustBack(v, str1);
v = PustBack(v, str2);
v = PustBack(v, str3);
v = PustBack(v, str4);
str* v1 = v->vector[0];
str* v2 = v->vector[1];
str* v3 = v->vector[2];
str* v4 = v->vector[3];
VectorIter *iter = VectorGetIter(v, 0);
str* vv1 = VectorNext(iter);
str* vv2 = VectorNext(iter);
str* vv3 = VectorNext(iter);
str* vv4 = VectorNext(iter);*/







