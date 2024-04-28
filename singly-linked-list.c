/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h> //표준입출력을 담당하는 <stdio.h> 헤더파일 선언
#include<stdlib.h> //동적할당을 담당하는 <stdlib.h> 헤더파일 선언

/* 필요한 헤더파일 추가 */

typedef struct Node { //node 구조체 선언
	int key;
	struct Node* link;
} listNode;

typedef struct Head { //head 구조체 선언
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); //headNode 초기화 함수 원형 선언
int freeList(headNode* h); //리스트 메모리 해제 함수 원형 선언

int insertFirst(headNode* h, int key); //첫번째 노드 삽입 함수 원형 선언
int insertNode(headNode* h, int key); //노드 삽입 함수 원형 선언
int insertLast(headNode* h, int key); //마지막 노드 삽입 함수 원형 선언

int deleteFirst(headNode* h); //첫번째 노드 삭제 함수 원형 선언
int deleteNode(headNode* h, int key); //노드 삭제 함수 원형 선언
int deleteLast(headNode* h); //마지막 노드 삭제 함수 원형 선언
int invertList(headNode* h); //리스트 역순 함수 원형 선언

void printList(headNode* h); //리스트 출력 함수 원형 선언

int main() //main함수 시작
{
	printf("[----- [배정민] [2023041088] -----]\n");

	char command; 
	int key;
	headNode* headnode=NULL;


	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)  // headNode가 NULL이 아닐 경우
		freeList(h); // freeList 함수 호출하여 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // headNode에 대한 메모리 동적할당
	temp->first = NULL; // headNode의 first를 NULL로 초기화
	return temp; // temp값 반환
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; // 리스트의 첫번째 노드를 가리키는 포인터

	listNode* prev = NULL; // 이전 노드를 가리키는 포인터
	while(p != NULL) { // 리스트의 끝까지 반복
		prev = p; // 이전 노드를 현재 노드로 지정
		p = p->link; // 현재 노드를 다음 노드로 지정
		free(prev); // 이전 노드 메모리 해제
	}
	free(h); // 헤드 노드 메모리 해제
	return 0; //0값 반환
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 동적할당
	node->key = key; // 새로운 노드의 key에 key값 저장

	node->link = h->first; // 새로운 노드의 link를 첫번째 노드로 지정
	h->first = node; // 첫번째 노드를 새로운 노드로 지정

	return 0; //0값 반환
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 동적할당.

	node->key = key; // 새로운 노드의 key에 key값 저장
	node->link = NULL; // 새로운 노드의 link를 NULL로 초기화

	if (h->first == NULL) // 리스트가 비어있을 경우
	{
		h->first = node; // 새로운 노드를 첫번째 노드로 지정
		
		return 0; //0값 반환
	}

	listNode* n = h->first; // 리스트의 첫번째 노드를 가리키는 포인터
	listNode* trail = h->first; // 이전 노드를 가리키는 포인터

	while(n != NULL) // 리스트의 끝까지 반복
	{
		if(n->key >= key) // 현재 노드의 key값이 입력받은 key값보다 크거나 같을 경우
		{
			if(n == h->first) // 현재 노드가 첫번째 노드일 경우
			{
				h->first = node; // 새로운 노드를 첫번째 노드로 지정
				node->link = n; // 새로운 노드의 link를 현재 노드로 지정
			} 
			else 
			{
				node->link = n; // 새로운 노드의 link를 현재 노드로 지정
				trail->link = node; // 이전 노드의 link를 새로운 노드로 지정
			}

			return 0; //0값 반환
		}

		trail = n; // 이전 노드를 현재 노드로 지정
		n = n->link; // 현재 노드를 다음 노드로 지정
	}

	trail->link = node; // 이전 노드의 link를 새로운 노드로 지정

	return 0; //0값 반환
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 동적할당

	node->key = key; // 새로운 노드의 key에 key값 저장
	node->link = NULL; // 새로운 노드의 link를 NULL로 초기화

	if (h->first == NULL) // 리스트가 비어있을 경우
	{
		h->first = node; // 새로운 노드를 첫번째 노드로 지정
		
		return 0; //0값 반환
	}

	listNode* n = h->first; // 리스트의 첫번째 노드를 가리키는 포인터
	
	while(n->link != NULL) // 리스트의 끝까지 반복
	{
		n = n->link; // 현재 노드를 다음 노드로 지정
	}
	
	n->link = node; // 현재 노드의 link를 새로운 노드로 지정

	return 0; //0값 반환
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) // 리스트가 비어있을 경우
	{
		printf("지울 노드가 없습니다.\n");
		
		return 0; //0값 반환
	}

	listNode* n = h->first; // 리스트의 첫번째 노드를 가리키는 포인터

	h->first = n->link; // 첫번째 노드를 두번째 노드로 지정
	
	free(n); // 첫번째 노드 메모리 해제

	return 0; //0값 반환
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) // 리스트가 비어있을 경우
	{
		printf("지울 노드가 없습니다.\n");
		
		return 0; //0값 반환
	}

	listNode* n = h->first; // 리스트의 첫번째 노드를 가리키는 포인터
	listNode* trail = NULL; // 이전 노드를 가리키는 포인터

	while(n != NULL) // 리스트의 끝까지 반복
	{
		if(n->key == key) // 현재 노드의 key값이 입력받은 key값과 같을 경우
		{

			if(n == h->first) // 현재 노드가 첫번째 노드일 경우
			{
				h->first = n->link; // 첫번째 노드를 두번째 노드로 지정
			} 
			else 
			{
				trail->link = n->link; // 이전 노드의 link를 현재 노드의 link로 지정
			}
			
			free(n); // 현재 노드 메모리 해제
			
			return 0; //0값 반환
		}

		trail = n; // 이전 노드를 현재 노드로 지정
		n = n->link; // 현재 노드를 다음 노드로 지정
	}

	printf("%d 값을 가지고 있는 노드가 없습니다.\n", key);

	return 0; //0값 반환

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) // 리스트가 비어있을 경우
	{
		printf("지울 노드가 없습니다.\n");
		
		return 0; //0값 반환
	}

	listNode* n = h->first; // 리스트의 첫번째 노드를 가리키는 포인터
	listNode* trail = NULL; // 이전 노드를 가리키는 포인터

	if(n->link == NULL) // 리스트에 노드가 하나만 있을 경우
	{
		h->first = NULL; // 리스트를 비움
		
		free(n); // 첫번째 노드 메모리 해제
		
		return 0; //0값 반환
	}

	while(n->link != NULL) // 리스트의 끝까지 반복
	{
		trail = n; // 이전 노드를 현재 노드로 지정
		n = n->link; // 현재 노드를 다음 노드로 지정
	}

	trail->link = NULL; // 이전 노드의 link를 NULL로 지정
	
	free(n); // 현재 노드 메모리 해제

	return 0; //0값 반환
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	if(h->first == NULL) // 리스트가 비어있을 경우 
	{
		printf("뒤집을 노드가 없습니다.\n");
		
		return 0; //0값 반환
	}
	
	listNode *n = h->first; // 리스트의 첫번째 노드를 가리키는 포인터
	listNode *trail = NULL; // 이전 노드를 가리키는 포인터
	listNode *middle = NULL; // 현재 노드를 가리키는 포인터

	while(n != NULL) // 리스트의 끝까지 반복
	{
		trail = middle; // 이전 노드를 현재 노드로 지정
		middle = n; // 현재 노드를 다음 노드로 지정
		n = n->link; // 현재 노드를 다음 노드로 지정
		middle->link = trail; // 현재 노드의 link를 이전 노드로 지정
	}

	h->first = middle; // 첫번째 노드를 마지막 노드로 지정

	return 0; //0값 반환
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

