struct Node {
	int data;
	struct Node *next;
};

struct Node *createNode(int data) {
	struct Node *p = (struct Node * )malloc(sizeof(struct Node));
	p->data = data;
	p->next = NULL;
	return p;
}

//头插法
struct Node *inserthead(struct Node *head, int data) {
	struct Node *add = createNode(data);
	if (head == NULL) {
		return add;
	}
//	struct Node *p = head;
//	head = add;
//	head->next = p;
//	return head;
	add->next = head;
	return add;
}

//尾插法
struct Node *insert(Node *head, int data) {
	struct Node *add = createNode(data);
	if (head == NULL) {
		return add;
	}
	while (head->next != NULL) {
		head = head->next;
	}
	head->next = add;
	return head;
}

struct Node *search(Node *head, int data) {
	if (head == NULL || head->data == data) {
		return head;
	}
	struct Node *p = head;
	while (p->next != NULL) {
		if (p->data == data) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

struct Node *del(Node *head, int data) {
	if (head == NULL) {
		return head;
	}
	if (head->data == data) {
		struct Node *p = head->next;
		free(head);
		return p;
	}
	struct Node *tail = head;
	struct Node *p = head->next;
	while (p != NULL) {
		if (p->data == data) {
			break;
		}
		tail = p;
		p = p->next;
	}
	if (p != NULL && p->data == data) {
		tail->next = p->next;
		free(p);
	}
	return head;
}

//清除链表
struct destoty(Node *head) {
	if (head != NULL) {
		destory(head->next);
		free(head);
	}
}