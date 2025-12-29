        #include <stdio.h> // 1230127_lujainAlawneh_sec4
#include <stdlib.h>
#include <string.h>
typedef struct node {
    int taskId;
    char  name [100];
    char  date [100] ;
    double  duration ;
    struct node *right;
    struct node *left;
    int counter;
    int performed ;
}node;
void displayMainMenu( ) ;
node* insert ( node*root,  int rootId ,char theName [ 100],char theDate [100],double theDuration);
node* loadTasks(  FILE *input ,node* root  );
void displayTasks( node *root  );
node* addTask(node* root, int key );
node* findMin( node*root ) ;
node* deleteTask( int x ,node* root   ) ;
void searchTask(node* root,  char taskNameString[100] );
void performTask(node* root, int taskId);
node*sortTreeByTaskId(node*root,int rootId ,char theName [ 100],char theDate [100],double theDuration  , int counter ,int performed );
node* RestructureToId(node* root   );
node*fromRootToTemp(node* root );
node*MakeEmpty( node* T );
node*sortTreeByTaskName(node*root,int rootId ,char theName [ 100],char theDate [100],double theDuration  , int counter ,int performed );
node* RestructureToName(node* root  ) ;
node* loopDataFromTempToRoot(node* root ,node* temp );
node*loopDataFromTempToRootForId(node* root ,node* temp ) ;
void viewPerformedTasks(node* root ) ;
void viewUnPerformedTasks(node* root );
node*sortTreeByDuration(node*root,int rootId ,char theName [ 100],char theDate [100],double theDuration  , int counter ,int performed );
node*loopDataFromTempToRootDuration(node* root ,node* temp );
node* RestructureToDuration(node* root  ) ;
node*loopDataFromTempToRootDate(node* root ,node* temp );
node* RestructureToDate(node* root  );
node*sortTreeByTaskDate(node*root,int rootId ,char theName [ 100],char theDate [100],double theDuration  , int counter ,int performed ) ;
int numberOfInternalNodes(node* root );
int numberOfLeaf(node* root );
int treeSize(node* root );
int treeHeight(node* root );
int findDate(node* root , char date[]);
int main(void) {
    FILE *input = fopen("tasks.txt", "r");
    if (input == NULL) {
        printf("Error opening file\n");
        return 1 ;
    }
    int choice ;
    node * root = NULL;
    node * temp = NULL;
    do {
        displayMainMenu( );

        scanf("%d",&choice);
        switch(choice) {

            case 1:
             root =  loadTasks( input ,root  );

            break;
            case 2:
                printf("enter task id :");
            int key ;
            scanf("%d",&key);
                root = addTask(  root,  key );

                break;
            case 3:
printf("enter the id of task you want to delete  :");
            int x ;
            scanf("%d",&x);
                root =  deleteTask(   x, root   ) ;
                break;
            case 4:
                printf("Enter the Task name you want to search for ");
            char taskNameString[100];
            gets(taskNameString);
            gets(taskNameString);
             searchTask(  root, taskNameString );

                break ;
            case 5:
                printf("Enter ID for task  you  want to perform ");
            int taskId;
            scanf("%d",&taskId);
            performTask( root, taskId);
                break;
            case 6:
     root = RestructureToName(root) ;
            viewUnPerformedTasks( root );
                break;
            case 7:
                root = RestructureToId( root  );
            viewPerformedTasks(  root ) ;
                break;
            case 8:
printf("\nEnter the Task Restructure type want to view  :");
            printf("\nEnter 1 for Task ID  :");
            printf("\nEnter 2 for Task Name :");
            printf("\nEnter 3 for Task Date :");
            printf("\nEnter 4 for Task Duration :");
            int m;
            scanf("%d",&m);
            switch(m) {
                case 1:
                    root =RestructureToId( root  );
                    break;
                case 2:
                    root =RestructureToName(root) ;
                    break ;
                case 3:
                    root =RestructureToDate(  root  );
                displayTasks(  root  );
                    break;
                case 4:
                    root =RestructureToDuration(  root  ) ;
                    break;
                default:
                    printf("\nNo choice like this! Please try again.\n");
                break;
            }
                break;
            case 9:
                printf("\ntree height :%d",treeHeight(root));
            printf("\ntree size :%d",treeSize( root));
            printf("\nnumber of internal nodes :%d",numberOfInternalNodes(root) );
            printf("\nnumber of leavs :%d",numberOfLeaf( root ));
                break ;
            case 10:
                printf("Thank you for using My ask Management System .GoodBye.\n");
            break;
            default :
                printf("\nNo such operation! Please try again.\n");
            break;

        }
    }while(choice != 10 );
    fclose(input);
    return 0;
}
void displayMainMenu( ) {
    printf("\n");
    printf("\nWelcome to  the Task Management System\n");
    printf("please select an operation.....\n");
    printf("1-Load Tasks File:\n");
    printf("2-Add a New Task :\n");
    printf("3-Delete a Task:\n");
    printf("4-Search for a Task:\n");
    printf("5-perform a Task\n");
    printf("6-View Unperformed Tasks\n");
    printf("7- View Performed Tasks\n");
    printf("8-Restructure the Tasks BST\n");
    printf("9-View the tasks BST info\n");
    printf("10-Exit\n");
    printf("please enter your choice \n") ;
    printf("\n");
}

node* insert ( node*root,  int rootId ,char theName [ 100],char theDate [100],double theDuration)  {
    if (  root== NULL ) {
         root  = (node*)malloc(sizeof(node));
        if (root == NULL) {
            printf("Memory allocation failed \n");
            return NULL;
        }
        root->taskId = rootId;
        strcpy(root->name,theName);
        strcpy(root->date,theDate);
        root->duration = theDuration;
        root ->counter =1;
        root ->performed =0;// initially  , the task is not performed
        root->left  = root ->right = NULL;
        return root;
    }
    else if (root->taskId > rootId) {
        root->left = insert (  root->left,    rootId ,  theName  , theDate  ,  theDuration) ;
    }
    else if (root->taskId < rootId) {
        root->right =  insert (  root->right,    rootId ,  theName  , theDate  ,  theDuration) ;
    }
    else {
        root->counter++;
    }
    return root;

}

node* loadTasks(  FILE *input ,node* root   ) {
    char array[100];
    char temp  [100];
    int rootId ;
    char theName[100];
    double theDuration;
    char theDate[100];
    while ( fgets(array,sizeof(array),input) != NULL) {
        char *token = strtok(array,"#");
        rootId = atoi(token);
        strcpy (temp,strtok(NULL,"#")) ;
        strcpy ( theName,temp ) ;
        strcpy (temp ,strtok(NULL,"#")) ;
        strcpy (theDate,temp  ) ;
        theDuration = atof(strtok(NULL,"#"));
        root = insert ( root, rootId ,theName , theDate ,theDuration) ;
    }
    printf("\ndata loaded successfully !\n");
    return root;
}

void displayTasks(node *root) {
   if(root == NULL){
    return;
   }
   displayTasks( root->left);
    printf("\nTask ID : %d",root->taskId);
        printf("\nName : %s",root->name);
        printf("\nDate : %s",root->date);
        printf("\nDuration : %lf",root->duration);
        printf("\nCounter : %d",root->counter);
        printf("\nperformed : %d",root->performed);
         displayTasks( root->right);

}
node* addTask(node* root, int key ) {
    if (root == NULL) {
        root  = (node*)malloc(sizeof(node));
        if (root == NULL) {
            printf("Memory allocation failed \n");
        }
        root ->taskId = key ;
        printf("Enter the Task name: \n");
        gets(root->name );
        gets(root->name );
        printf("Enter the Task Date: \n");
        gets(root->date );

        printf("Enter the Task Duration: \n");
        scanf("%lf",&root->duration);
        printf("A new task added successfully !");
        root->counter = 0;
        root->left  = root ->right = NULL;

    }
    else if (root->taskId > key) {
        root->left = addTask(root->left, key);
    }
    else if (root->taskId < key) {
        root->right = addTask(root->right, key);
    }
    else {
        root->counter++;
    }
    return root;

}
node* deleteTask( int x ,node* root   ){
    node*  TmpCell;

    if( root  == NULL )
        printf( "Element not found" );
    else if( x < root ->taskId )
        root->left = deleteTask( x, root->left );
    else if( x > root->taskId )
        root->right = deleteTask( x, root->right );
    else
        if( root->left && root->right )

        {
            TmpCell = findMin( root ->right );
           root ->taskId = TmpCell->taskId;
            root->duration = TmpCell->duration;
            strcpy(root->name,TmpCell->name);
            strcpy(root->date,TmpCell->date);
            root->counter = TmpCell->counter;
            root->performed = TmpCell->performed;
            root ->right = deleteTask( root->taskId, root ->right );

        }
    else
    {
        TmpCell = root;
        if( root->left == NULL )
                root= root->right;
        else if( root->right == NULL )
           root= root->left;
        free( TmpCell );
        printf("\ndata delete successfully !");
    }
    return root ;
    }

node* findMin( node*root ){

    if( root == NULL)
        return NULL;

    else if( root-> left == NULL)
        return root;

    else
        return findMin( root->left );

}
void searchTask(node* root, char taskNameString[100] ) {
    if (root == NULL) {
        return;
    }
    searchTask( root->right, taskNameString  );
    searchTask( root->left, taskNameString  );
    if  (strcmp(root->name,taskNameString) == 0) {
        printf("\nTask ID: %d", root->taskId);
        printf("\nTask Name: %s", root->name);
        printf("\nTask Date: %s", root->date);
        printf("\nTask Duration: %lf", root->duration);
        printf("\nTask Counter: %d", root->counter);
        printf("\nTask Performed: %d", root->performed);

        return;
    }
}
void performTask(node* root, int taskId) {
    if (root == NULL) {
        return;
    }
     performTask( root->right, taskId   );
   performTask ( root->left,  taskId );
    if (root->taskId == taskId) {
        root->performed =   1;
        printf("task performed successfully");
        return;
    }
}

node*sortTreeByTaskId(node*root,int rootId ,char theName [ 100],char theDate [100],double theDuration  , int counter ,int performed ) {
    if (  root== NULL ) {
        root  = (node*)malloc(sizeof(node));
        if (root == NULL) {
            printf("Memory allocation failed \n");
            return NULL;
        }
        root->taskId = rootId;
        strcpy(root->name,theName);
        strcpy(root->date,theDate);
        root->duration = theDuration;
        root ->counter = counter ;
        root ->performed =performed ;// initially  , the task is not performed
        root->left  = root ->right = NULL;
        return root;
    }
    else if ( root->taskId > rootId ) {
        root->left =   sortTreeByTaskId(  root->left,    rootId ,  theName  , theDate  ,  theDuration , counter ,performed );
    }
    else if (root->taskId < rootId ) {
        root->right =  sortTreeByTaskId (  root->right,    rootId ,  theName  , theDate  ,  theDuration , counter ,performed );
    }
    else {
        root->counter++;
    }
    return root;
}

node* RestructureToId(node* root  ) {
    if (root == NULL) {
        return NULL;
    }
    node*temp =fromRootToTemp(  root   );
    root = MakeEmpty ( root );
    root =  loopDataFromTempToRootForId(  NULL ,  temp );// because when root is deleted  , its null

    free(temp);
    return root ;

}
node*fromRootToTemp(node* root   ) { //  using this function to take copy  from root
        if (root == NULL) {
            return NULL;
        }
    node* temp = (node*)malloc(sizeof(node));
    if (temp == NULL) {
        printf("Memory allocation failed \n");
        return NULL;
    }
        temp->taskId = root->taskId;
        strcpy(temp->name,root->name );
        strcpy(temp->date, root->date);
        temp->duration = root->duration ;
        temp ->counter = root->counter;
        temp ->performed =root->performed ;

    temp->left = fromRootToTemp(root->left);
    temp->right = fromRootToTemp(root->right);
        return temp;


}
node*MakeEmpty( node* T ){
    if( T != NULL ){
        MakeEmpty( T->left );
        MakeEmpty( T->right );
        free( T );
    }
    return NULL;

}
node*sortTreeByTaskName(node*root,int rootId ,char theName [ 100],char theDate [100],double theDuration  , int counter ,int performed ) {
    if (  root== NULL ) {
        root  = (node*)malloc(sizeof(node));
        if (root == NULL) {
            printf("Memory allocation failed \n");
            return NULL;
        }
        root->taskId = rootId;
        strcpy(root->name,theName);
        strcpy(root->date,theDate);
        root->duration = theDuration;
        root ->counter = counter ;
        root ->performed =performed ;// initially  , the task is not performed
        root->left  = root ->right = NULL;
        return root;
    }
    else if (   strcmp(root->name,theName) > 0 ) {
        root->left =   sortTreeByTaskName(  root->left,    rootId ,  theName  , theDate  ,  theDuration , counter ,performed );
    }
    else if (   strcmp(root->name,theName) < 0 ) {
        root->right =  sortTreeByTaskName (  root->right,    rootId ,  theName  , theDate  ,  theDuration , counter ,performed );
    }
    else {
        root->counter++;
    }
    return root;
}
node* RestructureToName(node* root  ) {
    if (root == NULL) {
        return NULL;
    }
    node*temp =fromRootToTemp(  root   );
    root = MakeEmpty ( root );
   root = loopDataFromTempToRoot(  NULL ,  temp );// because when root is deleted  , its null

    free(temp);
    return root ;

}
node*loopDataFromTempToRoot(node* root ,node* temp ) {
    if (temp == NULL) {
        return root;
    }
    root = sortTreeByTaskName(root,temp->taskId,temp->name,temp->date,temp->duration , temp->counter ,temp->performed );
    root =loopDataFromTempToRoot( root ,  temp->left );
    root = loopDataFromTempToRoot( root ,  temp->right );
    return root ;
}
node*loopDataFromTempToRootForId(node* root ,node* temp ) {
    if (temp == NULL) {
        return root;
    }
    root = sortTreeByTaskId(root,temp->taskId,temp->name,temp->date,temp->duration , temp->counter ,temp->performed );
    root =loopDataFromTempToRootForId( root ,  temp->left );
    root = loopDataFromTempToRootForId( root ,  temp->right );
    return root ;
}
void viewPerformedTasks(node* root ) {
    if (root == NULL) {
        return;
    }
    viewPerformedTasks(root->left);
    if (root -> performed == 1) {
        printf("Task ID : %d\n",root->taskId);
    printf("Name : %s\n",root->name);
    printf("Date : %s\n",root->date);
    printf("Duration : %d\n",root->duration);
    printf("Counter : %d\n",root->counter);
    }
    viewPerformedTasks(root->right);
}
void viewUnPerformedTasks(node* root ) {
    if (root == NULL) {
        return;
    }
    viewUnPerformedTasks(root->left);
    if (root -> performed == 0) {
        printf("Task ID : %d\n",root->taskId);
        printf("Name : %s\n",root->name);
        printf("Date : %s\n",root->date);
        printf("Duration : %d\n",root->duration);
        printf("Counter : %d\n",root->counter);
    }
    viewUnPerformedTasks(root->right);
}



node*sortTreeByDuration(node*root,int rootId ,char theName [ 100],char theDate [100],double theDuration  , int counter ,int performed ) {
    if (  root== NULL ) {
        root  = (node*)malloc(sizeof(node));
        if (root == NULL) {
            printf("Memory allocation failed \n");
            return NULL;
        }
        root->taskId = rootId;
        strcpy(root->name,theName);
        strcpy(root->date,theDate);
        root->duration = theDuration;
        root ->counter = counter ;
        root ->performed =performed ;// initially  , the task is not performed
        root->left  = root ->right = NULL;
        return root;
    }
    else if (   root->duration > theDuration ) {
        root->left =   sortTreeByDuration(  root->left,    rootId ,  theName  , theDate  ,  theDuration , counter ,performed );
    }
    else if (   root->duration < theDuration ) {
        root->right =  sortTreeByDuration (  root->right,    rootId ,  theName  , theDate  ,  theDuration , counter ,performed );
    }
    else {
        root->counter++;
    }
    return root;
}
node* RestructureToDuration(node* root  ) {
    if (root == NULL) {
        return NULL;
    }
    node*temp =fromRootToTemp(  root   );
    root = MakeEmpty ( root );
    root = loopDataFromTempToRootDuration(  NULL ,  temp );// because when root is deleted  , its null

    free(temp);
    return root ;

}
node*loopDataFromTempToRootDuration(node* root ,node* temp ) {
    if (temp == NULL) {
        return root;
    }
    root = sortTreeByDuration(root,temp->taskId,temp->name,temp->date,temp->duration , temp->counter ,temp->performed );
    root = loopDataFromTempToRootDuration( root ,  temp->left );
    root =  loopDataFromTempToRootDuration( root ,  temp->right );
    return root ;
}
int findDate(node* root , char date[]) {
    char tempString1[100];
    char tempString2[100];
    strcpy(tempString1,root->date);
    strcpy(tempString2,date);

    char *token = strtok( tempString1,"/");
    int year = atoi(token);
    token = strtok(NULL,"/");
    int month = atoi(token);
    token = strtok(NULL,"/");
    int day = atoi(token);

     token  = strtok( tempString2 ,"/");
    int year2 = atoi(token);
    token = strtok(NULL,"/");
    int month2 = atoi(token);
    token = strtok(NULL,"/");
    int day2 = atoi(token);

    if (year>year2 )
        return 0;
    if (month>month2)
        return 0;
    if (day>day2)
        return 0;
     if (year<year2)
         return 1;
         if (month<month2)
             return 1;
             if(day<day2)
        return 1;

    else
        return 2;

}
node*sortTreeByTaskDate(node*root,int rootId ,char theName [ 100],char theDate [100],double theDuration  , int counter ,int performed ) {
    if (  root== NULL ) {
        root  = (node*)malloc(sizeof(node));
        if (root == NULL) {
            printf("Memory allocation failed \n");
            return NULL;
        }
        root->taskId = rootId;
        strcpy(root->name,theName);
        strcpy(root->date,theDate);
        root->duration = theDuration;
        root ->counter = counter ;
        root ->performed =performed ;// initially  , the task is not performed
        root->left  = root ->right = NULL;
        return root;
    }
    else if (findDate(  root ,theDate)  ==0) {
        root->left =   sortTreeByTaskName(  root->left,    rootId ,  theName  , theDate  ,  theDuration , counter ,performed );
    }
    else if (   findDate(  root ,theDate)  ==1 ) {
        root->right =  sortTreeByTaskName (  root->right,    rootId ,  theName  , theDate  ,  theDuration , counter ,performed );
    }
    else {
        root->counter++;
    }
    return root;
}
node* RestructureToDate(node* root  ) {
    if (root == NULL) {
        return NULL;
    }
    node*temp =fromRootToTemp(  root   );
    root = MakeEmpty ( root );
   root = loopDataFromTempToRootDate(  NULL ,  temp );// because when root is deleted  , its null

    free(temp);
    return root ;

}
node*loopDataFromTempToRootDate(node* root ,node* temp ) {
    if (temp == NULL) {
        return root;
    }
    root = sortTreeByTaskDate(root,temp->taskId,temp->name,temp->date,temp->duration , temp->counter ,temp->performed );
    root =loopDataFromTempToRootDate( root ,  temp->left );
    root = loopDataFromTempToRootDate( root ,  temp->right );
    return root ;
}
int treeHeight(node* root ) { // since the hight is the path from root to the deepest element
    if (root == NULL) {
        return 0;
    }
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    if (leftHeight > rightHeight) {
        return 1+leftHeight;
    }
    else {
        return 1+rightHeight;
    }
}
int treeSize(node* root ) { //  the # of nodes in the tree
    if (root == NULL) {
        return 0;
    }
    int leftSize = treeSize(root->left);
    int rightSize = treeSize(root->right);
    return 1+leftSize + rightSize;
}
int numberOfLeaf(node* root ) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return  numberOfLeaf( root ->left )+numberOfLeaf( root ->right ) ;
}
int numberOfInternalNodes(node* root ) {
    if (root == NULL) {
        return 0;
    }
    if ((root->left == NULL && root->right == NULL) || root== NULL  ){
        return 0;
    }

    return  1+numberOfInternalNodes( root ->left )+numberOfInternalNodes( root ->right ) ; //  the one is for the current node
}

