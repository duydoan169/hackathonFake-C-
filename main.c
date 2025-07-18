#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Project{
    int id;
    char title[100];
    char owner[100];
    int priority;
} Project;

typedef struct nodeSingle {
    struct nodeSingle* next;
    Project project;
}nodeSingle;

typedef struct nodeDouble {
    struct nodeDouble* next;
    Project project;
    struct nodeDouble* prev;
}nodeDouble;
nodeSingle* createNodeSingle(Project project){
    nodeSingle* newNode=malloc(sizeof(nodeSingle));
    newNode->next = NULL;
    newNode->project = project;
    return newNode;
}
nodeDouble* createNodeDouble(Project project){
    nodeDouble* newNode=malloc(sizeof(nodeDouble));
    newNode->next = NULL;
    newNode->prev=NULL;
    newNode->project = project;
    return newNode;
}
Project createProject(nodeSingle* headSingle) {
    Project project;
    if (headSingle == NULL) {
        project.id = 1;
    }else {
        nodeSingle* current=headSingle;
        while (current->next != NULL) {
            current = current->next;
        }
        project.id=current->project.id+1;
    }
    getchar();
    do {
        printf("nhap ten du an: ");
        fgets(project.title, 100, stdin);
        if (strcspn(project.title, "\n") == strlen(project.title)) {
            while (getchar()!='\n');
        }else {
            project.title[strcspn(project.title, "\n")]='\0';
        }
        if (project.title[0]=='\0') {
            printf("khong hop le\n");
        }
    }while (project.title[0]=='\0');
    do {
        printf("nhap ten nguoi quan ly: ");
        fgets(project.owner, 100, stdin);
        if (strcspn(project.owner, "\n") == strlen(project.owner)) {
            while (getchar()!='\n');
        }else {
            project.owner[strcspn(project.owner, "\n")]='\0';
        }
        if (project.owner[0]=='\0') {
            printf("khong hop le\n");
        }
    }while (project.owner[0]=='\0');
    printf("nhap do uu tien du an: ");
    scanf("%d", &project.priority);
    return project;
}
nodeSingle* push(nodeSingle* headSingle, Project project) {
    if (headSingle == NULL) {
        headSingle = createNodeSingle(project);
        return headSingle;
    }
    nodeSingle* current=headSingle;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = createNodeSingle(project);
    return headSingle;
}
void showProject(nodeSingle* headSingle, nodeDouble* headDouble) {
    if (headSingle == NULL) {
        printf("khong co du an hien tai\n\n");
    }else {
        printf("thong tin du an hien tai: \n");
        nodeSingle* current=headSingle;
        while (current!= NULL) {
            printf("ID: %d\n", current->project.id);
            printf("Ten du an: %s\n", current->project.title);
            printf("nguoi quan ly: %s\n", current->project.owner);
            printf("do uu tien: %d\n\n", current->project.priority);
            current = current->next;
        }
    }
    if (headDouble == NULL) {
        printf("khong co du an da hoan thanh\n");
    }else {
        printf("thong tin du an da hoan thanh: \n");
        nodeDouble* current=headDouble;
        while (current!= NULL) {
            printf("ID: %d\n", current->project.id);
            printf("Ten du an: %s\n", current->project.title);
            printf("nguoi quan ly: %s\n", current->project.owner);
            printf("do uu tien: %d\n\n", current->project.priority);
            current = current->next;
        }
    }
}
nodeSingle* deleteProject(nodeSingle* headSingle, int deleteId) {
    if (headSingle == NULL) {
        printf("khong co du an hien tai\n");
        return NULL;
    }
    if (headSingle->project.id == deleteId) {
        nodeSingle* temp=headSingle;
        headSingle=headSingle->next;
        free(temp);
        return headSingle;
    }
    nodeSingle* current=headSingle;
    while (current->next != NULL && current->next->project.id != deleteId) {
        current = current->next;
    }
    if (current->next == NULL) {
        printf("ID khong ton tai\n");
        return headSingle;
    }
    nodeSingle* temp=current->next;
    current->next = current->next->next;
    free(temp);
    return headSingle;
}
void updateProject(nodeSingle* headSingle, int updateId) {
    if (headSingle == NULL) {
        printf("khong co du an hien tai\n");
        return;
    }
    nodeSingle* current=headSingle;
    while (current != NULL && current->project.id != updateId) {
        current = current->next;
    }
    if (current== NULL) {
        printf("ID khong ton tai\n");
        return;
    }
    printf("thong tin du an: \n");
    printf("ID: %d\n", current->project.id);
    printf("Ten du an: %s\n", current->project.title);
    printf("nguoi quan ly: %s\n", current->project.owner);
    printf("do uu tien: %d\n\n", current->project.priority);
    getchar();
    do {
        printf("nhap ten du an: ");
        fgets(current->project.title, 100, stdin);
        if (strcspn(current->project.title, "\n") == strlen(current->project.title)) {
            while (getchar()!='\n');
        }else {
            current->project.title[strcspn(current->project.title, "\n")]='\0';
        }
        if (current->project.title[0]=='\0') {
            printf("khong hop le\n");
        }
    }while (current->project.title[0]=='\0');
    do {
        printf("nhap ten nguoi quan ly: ");
        fgets(current->project.owner, 100, stdin);
        if (strcspn(current->project.owner, "\n") == strlen(current->project.owner)) {
            while (getchar()!='\n');
        }else {
           current->project.owner[strcspn(current->project.owner, "\n")]='\0';
        }
        if (current->project.owner[0]=='\0') {
            printf("khong hop le\n");
        }
    }while (current->project.owner[0]=='\0');
    printf("nhap do uu tien du an: ");
    scanf("%d", &current->project.priority);
}
nodeDouble* markAsCompleted(nodeSingle* headSingle, nodeDouble* headDouble, int targetId, int* check) {
    nodeSingle* current=headSingle;
    while (current!= NULL && current->project.id != targetId) {
        current = current->next;
    }
    if (current==NULL) {
        printf("ID khong ton tai\n");
        *check=1;
        return headDouble;
    }
    if (headDouble == NULL) {
        headDouble=createNodeDouble(current->project);
        return headDouble;
    }
    nodeDouble* temp=headDouble;
    while (temp->next!=NULL) {
        temp=temp->next;
    }
    temp->next=createNodeDouble(current->project);
    return headDouble;
}
void sortByPriority(nodeSingle* headSingle) {
    if (headSingle == NULL || headSingle->next == NULL) {
        printf("khong du du an de sap xep\n");
        return;
    }
    nodeSingle* i=headSingle;
    nodeSingle* j=headSingle;
    while (i != NULL) {
        j=headSingle;
        while (j->next!=NULL) {
            if (j->project.priority > j->next->project.priority) {
                Project temp=j->next->project;
                j->next->project=j->project;
                j->project=temp;
            }
            j=j->next;
        }
        i=i->next;
    }
}
void searchByTitle(nodeSingle* headSingle, char* find) {
    nodeSingle* current=headSingle;
    int count=0;
    printf("ket qua tim kiem cho \"%s\"\n\n", find);
    while (current != NULL) {
        if (strstr(current->project.title, find)!=NULL) {
            printf("ID: %d\n", current->project.id);
            printf("Ten du an: %s\n", current->project.title);
            printf("nguoi quan ly: %s\n", current->project.owner);
            printf("do uu tien: %d\n\n", current->project.priority);
            count=1;
        }
        current=current->next;
    }
    if (count == 0) {
        printf("khong co du an voi ten \"%s\"\n", find);
    }
}
int main(void) {
    nodeSingle* headSingle=NULL;
    nodeDouble* headDouble=NULL;
    int n;
    do {
        printf("\n===========MENU===========\n");
        printf("1. them du an\n");
        printf("2. hien thi du an\n");
        printf("3. xoa du an\n");
        printf("4. cap nhat du an\n");
        printf("5. danh dau hoan thanh du an\n");
        printf("6. sap xep du an\n");
        printf("7. tim kiem du an\n");
        printf("8. thoat\n");
        printf("===========================\n");
        printf("nhap lua chon cua ban: ");
        scanf("%d", &n);
        switch (n) {
            case 1:
                Project project=createProject(headSingle);
                headSingle=push(headSingle, project);
                break;
            case 2:
                showProject(headSingle, headDouble);
                break;
            case 3:
                int deleteId;
                printf("nhap ID du an muon xoa: ");
                scanf("%d", &deleteId);
                headSingle=deleteProject(headSingle, deleteId);
                break;
            case 4:
                int updateId;
                printf("nhap ID du an muon sua: ");
                scanf("%d", &updateId);
                updateProject(headSingle, updateId);
                break;
            case 5:
                int check=0;
                int targetId;
                printf("nhap ID du an muon danh dau hoan thanh: ");
                scanf("%d", &targetId);
                headDouble=markAsCompleted(headSingle, headDouble, targetId, &check);
                if (check==0) {
                    headSingle=deleteProject(headSingle, targetId);
                }
                break;
            case 6:
                sortByPriority(headSingle);
                showProject(headSingle, headDouble);
                break;
            case 7:
                char find[50];
                getchar();
                printf("nhap ten du an muon tim: ");
                fgets(find, 50, stdin);
                if (strcspn(find, "\n")==strlen(find)) {
                    while (getchar()!='\n');
                }else {
                    find[strcspn(find, "\n")]='\0';
                }
                searchByTitle(headSingle, find);
                break;
            case 8:
                break;
            default:
                printf("khong hop le\n");
        }
    }while (n!=8);
    printf("da thoat chuong trinh");
    return 0;
}