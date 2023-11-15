typedef struct _stackElement {

	double number;
	struct _stackElement* next;
} stackElement;

stackElement* CreateElement(double number);
int readFile(char* buffer);
int StringIntoPostfix(stackElement* head, char* buffer, double* result);
int pop(stackElement* head, double* result);
int push(stackElement* head, stackElement* newStackElement);
int performOperation(stackElement* head, char* buffer, double* result);

int main() {

	stackElement head = { .number = 0.0,.next = NULL };
	char buffer[MAX_LEN] = "";
	double result = 0.0;

	if (readFile(buffer)) {
		return 1;
	}

	printf("postfix: %s \n", buffer);

	if (StringIntoPostfix(&head, buffer, &result)) {
		return 1;
	}

	printf("Result: %0.1f\n", result);

	return 0;
}

stackElement* CreateElement(dpuble number) {

	stackElement* newEl = NULL;

	newEl = (stackElement*)malloc(sizeof(stackElement));

	if (newEl == NULL) {
		perror("malloc");
		return NULL;
	}

	newEl->number = number;
	newEl->next = NULL;

	return newEl;
}

int readFile(char* buffer) {

	FILE* filepointer = NULL;
	filepointer = fopen("number.txt", "r");

	if (!filepointer) {

		perror("fopen");
		return 1;
	}

	fgets(buffer, MAX_LEN, filepointer);

	fclose(filepointer);

	return 0;

}

int StringIntoPostfix(stackElement* head, char* buffer, double* result) {

	char* currentBuffer = buffer;
	int status = 0;
	int numBytes = 0;
	double number = 0;
	char operation = 0;
	stackElement* newEl = NULL;

	while (strlen(currentBuffer) > 0) {

		status = sscanf(currentBuffer, "%lf %n", &number, &numBytes);

		if (status != 1) {
			sscanf(currentBuffer, "%c %n", &operation, &numBytes);

			if (performOperation(head, operation, result)) {
				return 1;
			}
			number = *result;

		}
		newEl = CreateElement(number);
		if (!newEl) {
			return 1;
		}

		push(head, newEl);
		currentBuffer += numBytes;

	}

	return 0;
}

int PerformOperation(stackElement* head, char operation, double* result) {

	double operand1 = 0.0;
	double operand2 = 0.0;

	if (pop(head, &operand1)) {
		return 1;
	}

	if (pop(head, operand2)) {
		return 1;
	}


	switch (operation) {

	case '+':
		*result = operand2 + operand1;
		break;
	case '-':
		*result = operand2 - operand1;
		break;
	case '*':
		*result = operand2 * operand1;
		break;
	case '/':
		*result = operand2 / operand1;
		break;
	default:
		printf("operation %c not supported!\n", operation);
		break;

	}

	return 0;
}

int pop(stackElement* head, double* result) {

	stackElement* toPop = NULL;

	toPop = head->next;
	if (!toPop) {
		printf("Stack empty!\n");
		return 1;
	}

	head->next = toPop->next;

	*result = toPop->number;

	free(toPop);

	return 0;
}

int push(stackElement* head, stackElement* newStackElement) {

	newStackElement->next = head->next;
	head->next = newStackElement;

	return 0;
}