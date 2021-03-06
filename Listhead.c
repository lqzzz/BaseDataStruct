#include "Listhead.h"
void list_del_all(Listhead* head,void del(void* )){
	Listhead *next_ = head->next_;
	while (next_ != head) {
		void* target = next_;
		LIST_MOVE_NEXT(&next_);
		del(target);
	}
	del(next_);
}

void* list_search(Listhead *listhead,void* key,int cmp(void*,void*)){
	void *curr_n = NULL;
	void *result_ = NULL;
	//LIST_FOREACH(curr_,listhead, 
	//	if (cmp(curr_, key) == 0) {
	//		result_ = curr_; 
	//		break;
	//	});
	do{
		Listhead *list_head = listhead;
		Listhead *curr_ = listhead;
		do{
			curr_n = curr_;
			if (cmp(curr_n, key) == 0) {
				result_ = curr_n;
				break;
			}
		}while((LIST_MOVE_NEXT(&curr_)) != list_head);
	} while (0);
	return result_;
}

void* list_prve(Listhead* head){
	return head->prve_;
}
