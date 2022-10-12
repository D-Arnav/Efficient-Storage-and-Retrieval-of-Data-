#define CURRENT_YEAR 2022

struct Node{
  long long int ssn;
  char name[30];
  struct Node* left;
  struct Node* right;
  int height;
}*nameRoot = NULL, *ssnRoot = NULL;

struct DOB{
  int day;
  char month[15];
  int year;
};

struct Customer{
  long long int ssn;
  char name[30];
  char address[100];
  struct DOB DOB;
  char status[10];
  long long int account_number;
  char account_type[10];
};

typedef struct Node Node;

typedef struct Customer Customer;

Customer customer[10000];

void resetData(){
  for (int i = 0; i < 10000; i++)
    customer[i].ssn = 0;
}

int hashFunction(long long int ssn){
  return (ssn * 4523) % 10000;
}

void linearProbingInsert(Customer C){
  int i = hashFunction(C.ssn);

  while(customer[i].ssn != 0 && i < 10000)
    i++;

  if (i >= 10000)
  {
    printf("No space left to add\n");
    return;
  }

  customer[i] = C;

}

void linearProbingDelete(long long int ssn){
  int i = hashFunction(ssn);

  while(customer[i].ssn != ssn && i < 10000)
    i++;

  if (i >= 10000)
  {
    printf("\nData not found to delete\n\n");
    return;
  }

  customer[i].ssn = 0;
  strcpy(customer[i].name, "\0");
}

int linearProbingSearch(long long int ssn){
  int i = hashFunction(ssn);

  while(customer[i].ssn != ssn && i < 10000)
    i++;

  if (i >= 10000)
  {
    printf("\nData not found to search\n\n");
    return -1;
  }

  return i;
}

int max(int a, int b);

int height(struct Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node *newNode(Customer C) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->ssn = C.ssn;
  strcpy(node->name, C.name);
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

int getBalance(struct Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

Node *insertNode(struct Node *node, Customer C) {
  if (node == NULL)
    return (newNode(C));

  if (strcmp(C.name, node->name) < 0)
    node->left = insertNode(node->left, C);
  else if (strcmp(C.name, node->name) > 0)
    node->right = insertNode(node->right, C);
  else
    return node;

  node->height = 1 + max(height(node->left),
               height(node->right));

  int balance = getBalance(node);
  if (balance > 1 && strcmp(C.name, node->left->name) < 0)
    return rightRotate(node);

  if (balance < -1 && strcmp(C.name, node->right->name) > 0)
    return leftRotate(node);

  if (balance > 1 && strcmp(C.name, node->left->name) > 0) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && strcmp(C.name, node->right->name) < 0) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

Node *minValueNode(struct Node *node) {
  struct Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

Node *deleteNode(struct Node *node, Customer C) {

  if (node == NULL)
    return node;

  if (strcmp(C.name, node->name) < 0)
    node->left = deleteNode(node->left, C);

  else if (strcmp(C.name, node->name) > 0)
    node->right = deleteNode(node->right, C);

  else {
    if ((node->left == NULL) || (node->right == NULL)) {
      struct Node *temp = node->left ? node->left : node->right;

      if (temp == NULL) {
        temp = node;
        node = NULL;
      } else
        *node = *temp;
      free(temp);
    } else {
      struct Node *temp = minValueNode(node->right);

      strcpy(node->name, temp->name);
      node->ssn = temp->ssn;

      Customer c;
      strcpy(c.name, temp->name);

      node->right = deleteNode(node->right, c);
    }
  }

  if (node == NULL)
    return node;

  node->height = 1 + max(height(node->left),
               height(node->right));

  int balance = getBalance(node);
  if (balance > 1 && getBalance(node->left) >= 0)
    return rightRotate(node);

  if (balance > 1 && getBalance(node->left) < 0) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && getBalance(node->right) <= 0)
    return leftRotate(node);

  if (balance < -1 && getBalance(node->right) > 0) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

void printPreOrder(struct Node *root) {
  if (root != NULL) {
    printf("%d / %s\n", root->ssn, root->name);
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}

long long int getSSN(struct Node *temp, char name[]){
  if (temp == NULL)
    return -1;

  if (strcmp(name, temp->name) == 0)
    return temp->ssn;
  else if (strcmp(name, temp->name) < 0)
    return getSSN(temp->left, name);
  else
    return getSSN(temp->right, name);
}

int checkIfMonth(char month[]){
  if ('z' <= month[0] && month[0] <= 'a')
    month[0] = month[0] - 'a' + 'A';
  return strcmp(month, "January") == 0 || strcmp(month, "january") == 0 || strcmp(month, "February") == 0 || strcmp(month, "february") == 0 || strcmp(month, "March") == 0 || strcmp(month, "march") == 0 || strcmp(month, "April") == 0 || strcmp(month, "april") == 0 || strcmp(month, "May") == 0 || strcmp(month, "may") == 0 || strcmp(month, "June") == 0 || strcmp(month, "june") == 0 || strcmp(month, "July") == 0 || strcmp(month, "july") == 0 || strcmp(month, "August") == 0 || strcmp(month, "august") == 0 || strcmp(month, "September") == 0 || strcmp(month, "september") == 0 || strcmp(month, "October") == 0 || strcmp(month, "october") == 0 || strcmp(month, "November") == 0 || strcmp(month, "november") == 0 || strcmp(month, "December") == 0 || strcmp(month, "december") == 0;
}

int checkIfDay(int day){
  return 1 <= day <= 31;
}

int checkIfYear(int year){
  return (1900 <= year && year <= CURRENT_YEAR - 18);
}

int checkIfMartialStatus(char status[]){
  if ('a' <= status[0] && status[0] <= 'z')
    status[0] = status[0] - 'a' + 'A';
  return strcmp(status, "Married") == 0 || strcmp(status, "Unmarried") == 0;
}

int checkIfAccountType(char type[]){
  if ('a' <= type[0] && type[0] <= 'z')
    type[0] = type[0] - 'a' + 'A';
  return strcmp(type, "Saving") == 0 || strcmp(type, "Fixed") == 0;
}

int digits(long long int n){
  int i = 0;
  while(n > 0)
  {
    n = n / 10;
    i++;
  }
  return i;
}

char *readString(char *input){
  char temp[100];
  while(scanf("%s", temp) != EOF)
  {

  }
}

int readCustomersFromFile(){
  Customer c;
  FILE *fp = fopen("C:\\Users\\arnav\\Documents\\Arnav\\C_programs\\DS_Project_Data.txt", "r");

  if (fscanf(fp, "%s", c.name) == -1)
    return -1;

  while(!feof(fp))
  {
    fscanf(fp, "%lld", &c.ssn);

    char temp[100];
    c.address[0] = '\0';

    fgets(temp, 100, fp);
    strcat(c.address, temp);
    strcat(c.address, "\n");
    fgets(temp, 100, fp);
    strcat(c.address, temp);
    strcat(c.address, "\n");
    fgets(temp, 100, fp);
    strcat(c.address, temp);
    strcat(c.address, "\n");
    fgets(temp, 100, fp);
    strcat(c.address, temp);
    strcat(c.address, "\n");

    fscanf(fp, "%d", &c.DOB.day);

    fscanf(fp, "%s", c.DOB.month);

    fscanf(fp, "%d", &c.DOB.year);

    fscanf(fp, "%s", c.status);

    fscanf(fp, "%s", c.account_type);

    fscanf(fp, "%lld", &c.account_number);

    ssnRoot = insertNode(ssnRoot, c);
    linearProbingInsert(c);



  fscanf(fp, "%s");
  }

  fclose(fp);
  return 0;
}

void writeCustomersToFile(Customer c){
  FILE *fp = fopen("dat.txt", "a");

  fprintf(fp, "%s\n", c.name);
  fprintf(fp, "%lld\n", c.ssn);
  fprintf(fp, "%s", c.address);
  fprintf(fp, "%d %s %d\n", c.DOB.day, c.DOB.month, c.DOB.year);
  fprintf(fp, "%s\n", c.status);
  fprintf(fp, "%s\n", c.account_type);
  fprintf(fp, "%d\n", c.account_number);

  fclose(fp);
}
