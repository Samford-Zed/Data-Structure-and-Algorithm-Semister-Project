//DATA STRUCTURES AND ALGORITHM: SEMISTER PROJECT
//GROUP MEMBERS:
//     NAME                ID No          SECTION
//1. NEGASA RETA           UGR/31072/15     6
//2. ROBA MEGERSA          UGR/31148/15     6
//3. SAMUEL ZENEBE         UGR/31182/15     6
//4. FEYISSA ALEMAYEHU     UGR/30535/15     6
//5. YESAK HAILEYESUS      UGR/31404/15     6

//submetted to Mr. Megersa
//submission date: 29/03/2024

#include<iostream>
#include <stdlib.h>
#include <cstdio>
#include <string>
#include <string.h>
using namespace std;


// Function declaration (prototype). They will be defined after main function.
void add_book_beg();
void add_book_end();
void add_book_any_pos(char*);
void create_node();
void display_from_beg(bool sort_flag);
char* string_to_char(char* ,  string);

bool is_sub_string(char* key, char* target, int tolerate);
void remove_book(bool sort_flag, char* based_on, char*keyword, char* pos_);
char* str_char(string s);


//Doubly linked list
struct Node {
    struct Node* prev;
    char* ISBN;
    char* author;
    char* title;
    char* date;
    char* no_page;

    struct Node* next;

};

Node *end;
Node *head;
Node *temp;
Node *current;
Node *sorted_end;
Node *sorted_head;
Node *sorted_current;


/* Function prototype which use Node as a variable or return value.
   They are declared after struct Node because either their argument
   or return values are Node type.*/

void print_book_info(Node*);
void copy_node(Node* node1, Node* node2);
Node** search  (char*  type, char* key_word);
void sort(struct Node** head_ref, char* based_on);
bool update(Node*, char*update_what, string update_to);

/*  count Number of books in the Book-List. (Global variable)
    It increases when book is added and decreased when book is removed. */
int count=0;
char* given_info;

/*  Used for fancy display of our data. They are default to length
    of the head - [No, Book title, ISBN, Author, Pub date, no_page...]*/
int longest_lines[6] = {2, 10, 4, 6, 8, 8};

/*We human beings make a wrong while typing. When you search for specific data,
How many characters do you TOLERATE to say This is thedata they are looking for.
It is defaulted to 2.*/
const int TOLERATE = 2;
int num_found_book = 0;
Node* found_books[10];                              // Store the top 10 books found in the system that matches a given keyword.

int main(){

    cout << "\n---WELCOME TO LIBRARY MANAGEMENT SYSTEM---"<< endl;
    cout << "These are the corresponding words to use the service:"<<endl;
    cout << "\t"<<"Add new book   - enter 1 \n";
    cout << "\t"<<"Search         - enter 2\n";
    cout << "\t"<<"Remove book    - enter 3\n";
    cout << "\t"<<"Sort           - enter 4\n";
    cout << "\t"<<"Display        - enter 5\n";
    cout << "\t"<<"Update         - enter 6\n";
    cout << "\t"<<"Exit           - Press 00\n";
    cout << "***NOTE: When you input a keyword for specific service don't input it with blank space at the end or beginning!"<<endl;

    string input;
    string add;
    string sorting_criteria="title";     // The default sorting criteria is based on title.
    string search_criteria="title";

    char* sorting_criteria_char;        // String input should be converted back to array of char for processing.
    char* search_criteria_char;
    bool sort_flag = false;             // Tells weather the Book lists are sorted or not.
    bool exit = false;

    while (!exit){

    cout <<"\n-----Please choose the service you want among these:-------"<<endl;
    cout<<"'add', 'display', 'remove', 'sort', 'update','search', 'exit' ---> ";
    cin.clear();
    getline(cin>>ws, input);

    // string comparison. Gives 0 if the two string are exactly the same.
    if (strcmp(input.c_str(), "00")==0){
        exit = true;    // turn on the exit flag.
        break;
    }
//to add a book to the list
    else if (strcmp(input.c_str(), "1")==0){
        cout<<"Where do you want to add? Please input the corresponding keyword."<<endl;
        cout<< "\tAt the beggining    - Press 1"<<endl;
        cout <<"\tAt the end          - Press 2"<<endl;
        cout<<"\tAlphabetically       - Press 3\n"<<endl;
        cout<<"Please choose one of the above:\t";
        getline(cin>>ws, add);
        if (strcmp(add.c_str(), "1")==0) add_book_beg();
        else if (strcmp(add.c_str(), "2")==0) add_book_end();
        else if (strcmp(add.c_str(), "3")==0){
            sort_flag = true;
            sorting_criteria_char = string_to_char(sorting_criteria_char, sorting_criteria);
            add_book_any_pos(sorting_criteria_char);   ////
        }
    }

    else if (strcmp(input.c_str(), "4")==0){
        string yes_no;      // Ask user to see weather he wants to display after sorting or not.
        char* yes_no_ch;
        cout<<"You want the book-list to be sorted based on what?"<<endl;
        cout <<"\tTitle     - title"<<endl;
        cout <<"\tAuthor    - author"<<endl;
        cout <<"\tISBN      - ISBN"<<endl;
        cout <<"Please input one of the above input:\t";
        getline(cin>>ws, sorting_criteria);
        // sorting_criteria_char = string_to_char(sorting_criteria_char, sorting_criteria);
        sorting_criteria_char = str_char(sorting_criteria);
        // cout<<"Your are sorting based on: "<<sorting_criteria_char<<endl;
        sort(&head, sorting_criteria_char);
        sort_flag = true;
        cout <<"Do you want to see the sorted book-list - yes/no?    --> ";

        getline(cin>>ws, yes_no);
        yes_no_ch = string_to_char(yes_no_ch, yes_no);
        if (strcmp(yes_no_ch, "yes")==0){
            display_from_beg(sort_flag);
        }
    }

     else if (strcmp(input.c_str(), "2")==0){
        /*  String variables: User input is string type.
            Char variables:   User input will be converted to char* before processing.
            Int variables:     Is used in removing giberish created by char pointer.*/
        string search_keyword;
        char *search_keyword_char;
        int len_criteria_str;

        int len_keyword_str;
        Node** books;

        cout<<"You want to search by  'title', 'ISBN'?\t";
        getline(cin>>ws, search_criteria);
        cin.clear();
        cout<<"The keyword:\t";
        getline(cin>>ws, search_keyword);

        // The following 6 lines are to convert string to char* datatype.
        search_criteria_char = &search_criteria[0];                     // Point to the first location of the string.
        search_keyword_char = &search_keyword[0];
        len_criteria_str = search_criteria.length();
        len_keyword_str = search_keyword.length();
        search_criteria_char[len_criteria_str] = '\0';                  // Ignores gibberish printed by the pointer after teminal characher.
        search_keyword_char[len_keyword_str] = '\0';

        books = search(search_criteria_char, search_keyword_char);

        if (books!=NULL){
            if (num_found_book >= 1){
                cout<<num_found_book<<" book found for "<<search_keyword<<" keyword."<<endl<<endl;
                for (int i=0; i<num_found_book;i++){
                    cout<<"\n===> Book #"<<i<<endl;
                    print_book_info(books[i]);
                }
            }
        }
            else{
                cout<<"No book with a given Keyword. Please retry with another keyword!"<<endl;

            }

    }
    else if (strcmp(input.c_str(), "3")==0){
        /*  String variables: User input is string type.
            Char variables:   User input will be converted to char* before processing.
            Int variables:     Is used in removing giberish created by char pointer.*/
        string pos;
        char* pos_ch;
        int pos_len;

        string based_on;
        char* based_on_ch;
        int based_on_len;

        string keyword;
        char* keyword_ch;
        int keyword_len;
        cout<<"Do you want to remove from end or with a given keyword?"<<endl;
        //cout<<"To remove at the beggining\t"<<"- begin"<<endl;
        cout<<"To remove from the end    \t"<<"- end"<<endl;
        cout<<"To remove with key        \t"<<"- key"<<endl;
        getline(cin>>ws, pos);
        pos_len = pos.length();
        pos_ch = &pos[0];
        pos_ch[pos_len] = '\0';



        if (pos == "key"){
            /*  If the user wanted to remove based on keyword. For example
                based on 'title' the user inputs the tile of the book. */
            cout<<"Do you want to remove based on 'title', or 'ISBN' or 'author'? "<<endl;
            getline(cin>>ws, based_on);
            based_on_len = based_on.length();
            based_on_ch = &based_on[0];
            based_on_ch[based_on_len]='\0';

            cout<<"Please insert the book?"<<endl;
            getline(cin>>ws, keyword);
            keyword_len = keyword.length();
            keyword_ch = &keyword[0];
            keyword_ch[keyword_len] = '\0';
            remove_book(sort_flag, keyword_ch, based_on_ch, pos_ch);

        }
        else{
            remove_book(sort_flag, keyword_ch, "title", pos_ch);
        }

    }
    else if (strcmp(input.c_str(), "5")==0){
        /* Displays the book store from beginning.
           If it is sorted It begins from sorted_head
           and traverse all the way to the tail.*/
        cout<<"\n \t -BOOKS IN THE STORE-"<<endl;
        display_from_beg(sort_flag);

    }
    else if (strcmp(input.c_str(), "6")==0){
        char* title;
        char* update_what;
        char* update_to;
        string title_str;
        string update_what_str;
        string update_to_str;
        Node** book;
        bool updated = false;


        while (!updated){
            // It breaks the loop when the update is successfull.
            cout<<"Please input the title of the book:--> ";
            getline(cin>>ws, title_str);
            cout<<"Which information do you want to update: ['title','ISBN', 'author', 'date', 'no_page'] --> ";
            getline(cin>>ws, update_what_str);
            cout<<"Please input the new information:--> ";
            getline(cin>>ws, update_to_str);

            title = string_to_char(title, title_str);
            update_what = string_to_char(update_what, update_what_str);

            book = search("title", update_what);
            updated = update(book[0], update_what, update_to_str);              // Update the first  book with the given title.

        }
        cout<<"Updated Successfully!"<<endl;
    }


    else{
        cout<<"\n*** Unrecognized Keyword! Please input the key words without blank space."<<endl;
        // cout<<"'add', 'display', 'remove', 'sort', 'update','search', 'exit'."<<endl;
    }
    }
return 0;

}

/////////////////////////////--- End of main() function --- ////////////////////////


// helper function to return max num of two numbers.
int max(int a, int b){
    if (a>b){
        return a;
    }
    return b;
}

/*This function is a meat of our whole program. It allows us
to create new node and add them any place we want. The user
will be inquired to input information. It will then be stored.*/
void create_node(){

    string book_info;
    int cnt_info = 0;
    temp = (struct Node*)malloc(sizeof(struct Node));

    cout << "--Please input the details of the books according to required info--"<<endl;
    temp->prev = NULL;
    temp->next = NULL;

    while(cnt_info<5){
    given_info = (char* ) malloc(100);

    switch(cnt_info){
        case 0:
            cout<< "Book title:";
            getline(cin>>ws, book_info);
            longest_lines[1] = max(longest_lines[1], book_info.length());       // Track the longest line among a given column. Useful for fancy display.
            temp->title = string_to_char(temp->title, book_info);               // The input value will be converted to char before stored.
            break;
        case 1:
            cout<< "ISBN:";
            getline(cin>>ws, book_info);
            longest_lines[2] = max(longest_lines[2], book_info.length());
            temp->ISBN = string_to_char(temp->ISBN, book_info);
            break;
        case 2:
            cout<< "author:";
            getline(cin>>ws, book_info);
            longest_lines[3] = max(longest_lines[3], book_info.length());
            temp->author = string_to_char(temp->author, book_info);
            break;
        case 3:
            cout<< "Publishing date:";
            getline(cin>>ws, book_info);
            longest_lines[4] = max(longest_lines[4], book_info.length());
            temp->date = string_to_char(temp->date, book_info);
            break;
        case 4:
            char* no_page_ch;
            cout<<"Number of Page:";
            getline(cin>>ws, book_info);
            longest_lines[5] = max(longest_lines[5], book_info.length());
            no_page_ch = string_to_char(no_page_ch, book_info);
            temp->no_page = no_page_ch;
            break;
    }
    cnt_info ++;

    }
    cout<< "--Added Successfully--"<< endl;
    count ++;       // Increases when A new book is added.

}

/*Print while we are searching for specific book.*/
void print_book_info(Node* book){
    cout << "Book title    \t"<<book->title<<endl;
    cout<< "ISBN:          \t"<< book->ISBN<<endl;
    cout<<"Author          \t"<<book->author<<endl;
    cout<<"Publication date\t"<<book->date<<endl;
    cout<<"Number of page  \t"<<book->no_page<<endl;
}

/*  It Is helper function that outputs the value of criteria of a node.
    For example if we need title of the first books we input head as the node
    parameter and title as criteria. */
char* criteria(Node* node, char *based_on){
    if (is_sub_string("title", based_on, 0)){
        return node->title;
    }
    // if (strcmp("title", criteria)){
    //     return node->title;
    // }
    else if (is_sub_string("author", based_on, 0)){
        return node->author;
    }
    else if (is_sub_string("ISBN", based_on, 0)){
        return node->ISBN;
    }
    else{
        cout<<"Key word Error. either ['title', 'author' or 'ISBN']"<<endl;
        return NULL;
    }
}

/*  This function compares a given string with other string and outputs weather it
    is the substring of that or not. It can tolerate a given amount of wrong character.
    It is defaulted to 2. We can change the parameter. */
bool is_sub_string(char* key, char* target, int tolerate){
    int key_len = strlen(key);                 // get how many character are in a given key char.
    int target_len = strlen(target);           // get how many character are in a given target char.

    for (int i=0; i<(target_len-key_len+1); i++){
        if (key[0]==target[i]){
            /*If the first character of the given keyword is found in the target,
            then compare the whole keywords With the characters after that point
            of target string for length of keyword. [check weather it substring].*/
              int not_same_count=0;
              int similar_count = 0;
              for(int j=0; j<key_len; j++){
                  bool same_or_not = key[j]==target[i+j];
                  if (!same_or_not){
                      // If one non similar character is found.
                      not_same_count ++;
                      similar_count = not_same_count;
                      if (not_same_count > tolerate){
                        not_same_count = 0;                         // For next substring check up make not_same_count = 0;
                        break;                                      // If more than 2 characters are not similar in a given substring then break;
                      }
                  }
              }
              if (similar_count <= tolerate){
                return true;                                        // If it is found then return true. Then No longer the loop goes on.
              }
        }
    }

}

Node** search (char *based_on, char* key_word){
    /* It traverse all the nodes from beginning searching for matching data with
    a given keyword. The user input two parameter.

    Param:  based_on:- Option for this will be either ['title', 'author' or 'ISBN'].
    param:  key_word:- What the user is searching for.
    Return: List of nodes of books matching the keywords.
    */
    temp = new Node;
    temp = head;
    bool found = false;
    char *current_node_value;

    while(temp!=NULL){
        current_node_value = criteria(temp, based_on);
        if (is_sub_string(key_word, current_node_value, TOLERATE)){

            found_books[num_found_book] = temp;
            num_found_book++;
            found = true;
        }
        if (temp->next == NULL){
            if (num_found_book == 0){
                cout<<"There is no book for '"<<key_word<<"' in this library."<<endl;
                return NULL;
            }

            else{
                return found_books;
            }
        }
        temp = temp->next;
    }
    return found_books;
}



// Add book @ begginning.
void add_book_beg(){

    // If the Book List is empty.
    temp = (struct Node*)malloc(sizeof(struct Node));
    if (head == NULL){
        create_node();
        head = temp;
        current = head;
    }

    // Else add before the head.
    else {
        //
        create_node();
        temp -> next = head;
        head -> prev = temp;
        head = temp;
    }

}

void add_book_end(){

    // If the Book List is empty.
    if (head == NULL){
        create_node();
        head = temp;
        current = head;
    }

    // Else add book at tail.
    else {
        create_node();
        current -> next = temp;
        temp -> prev = current;
        current = temp;
    }

}



// Sort using insertion sort algorithm.
void sortedInsert(struct Node** head_ref, struct Node* newNode, char* based_on)
{
    struct Node* current;

    // if list is empty
    if (*head_ref == NULL)
        *head_ref = newNode;

    // if the node is to be inserted at the beginning of the doubly linked list (*head_ref)->data >= newNode->data
    else if (criteria(*head_ref, based_on) > criteria(newNode, based_on)) {
        newNode->next = *head_ref;
        newNode->next->prev = newNode;
        *head_ref = newNode;
    }

    else {
        current = *head_ref;

        // locate the node after which the new node is to be inserted current->next->data < newNode->data
        while (current->next != NULL && (criteria(current->next, based_on) > criteria(newNode, based_on)))
            current = current->next;
        newNode->next = current->next;

        // if the new node is not inserted at the end of the list
        if (current->next != NULL)
            newNode->next->prev = newNode;

        current->next = newNode;
        newNode->prev = current;
    }
}

// Function to sort a doubly linked list using insertion sort
void sort(struct Node** head_ref, char* based_on)
{
    // Initialize 'sorted' - a sorted doubly linked list.
    struct Node* sorted = NULL;

    // Traverse the given doubly linked list and insert every node to 'sorted'
    // according to their ascending order.
    struct Node* current = *head_ref;
    while (current != NULL) {

        // Store next for next iteration
        struct Node* next = current->next;

        // removing all the links so as to create 'current' as a new node for insertion
        current->prev = current->next = NULL;

        // insert current in 'sorted' doubly linked list
        sortedInsert(&sorted, current, based_on);

        // Update current
        current = next;
    }

    // Update head_ref to point to sorted doubly linked list
    *head_ref = sorted;
    if ((*head_ref)->prev == NULL) {
        sorted_head = sorted;       // Make sorted head the new head.

    }
}

/* It adds book in the ascending order. Eg node
   containing book called 'a' will be before 'b'*/
void add_book_any_pos(char *sorted_based_on){
    if (sorted_head ==NULL){
        sort(&head, sorted_based_on);   //
    }

    create_node();
    Node *check;
    check = sorted_head;

        // Put the newly added book alphabetically.
        if (criteria(temp, sorted_based_on) < criteria(check, sorted_based_on)){
            while (check->next != NULL){
            temp -> next = sorted_head;
            sorted_head -> prev = temp;
            sorted_head = temp;
            }
        }

}


// Delete an element/ a node/ a book either from begining/end/at any position with a given key word.
void remove_book(bool sort_flag,  char*keyword, char* based_on, char* pos_){

    Node* current;
    if (sort_flag){
        current = sorted_head;
    }
    else{
        current = head;
    }

    if (current==NULL){
        cout<<"--There is no book in the store--"<<endl;
    }


    else if (current->next==NULL){
        // If there is only head/one book in store.
        if (sort_flag){
            sorted_head = NULL;
            free(sorted_head);
        }
        else{
            head = NULL;
            free(head);
        }

    }

    else{
        if (is_sub_string("begin", pos_, 0)){
            // If the user wants to remove from beggining.
            if (!sort_flag) head = head->next;              // If it is not sorted. make the new head head->next.
            else sorted_head = sorted_head->next;           // If it is sorted make the new head sorted_head->next.

            }
        else if (is_sub_string("end", pos_, 0)){
            while(current->next!=NULL){
            // Until Final node is reached, traverse.
            current = current->next;
            }
            current->prev->next = NULL;
            free(current);
            }
        else{
            while(current->next!=NULL){
            // Until Final node is reached, traverse.
            char* target_book = criteria(current, based_on);
            bool is_found = is_sub_string(keyword, target_book, TOLERATE);
            if (is_found) {
                // If the target node is found.
                if (current->next != NULL){
                    // If it is not final node, connect the previous node to the next of the target node.
                    current->prev = current->next;
                    current = NULL;
                }
                else{
                    // if it is the final node.
                    current = NULL;
                    }

                }
            else{
                cout<<"There is not book with the given Key word!"<<endl;
                }
            current = current->next;
            free(current);
            }

        }

    }
}

// Helper function for fancy display of the given data. It will print " " for specified amount.
void print_blank_space(int max_size, int len_data){
    int max_blank_after_the_last_char = max_size - len_data;
    for (int i=0; i<max_blank_after_the_last_char; i++){
        cout<<" ";
    }
    cout<<"\t";
}

/*  Function to display from beginning.
    First check weather it is sorted or not
    and traverse all the way to the final. */
void display_from_beg(bool sort_flag){

    Node* head_;
    if (sort_flag){

        head_ = sorted_head;
    }
    else{
        head_ = head;
    }

    temp = head_;
    if (temp==NULL){
        cout<<"\n No Books in the database."<<endl;
        return;
    }

    cout<<"These are the books Registered in this system"<< endl<<endl;
    int cnt = 0;
    cout << "No";
    print_blank_space(longest_lines[0], 1);
    cout<<"Book title";
    print_blank_space(longest_lines[1], 10);
    cout<< "ISBN";
    print_blank_space(longest_lines[2], 4);
    cout<< "Author";
    print_blank_space(longest_lines[3], 6);
    cout<<"Pub date";
    print_blank_space(longest_lines[4], 8);
    cout<<"Num page\t"<<endl;
    while (temp != NULL){
        cnt ++;
        cout<<cnt;
        print_blank_space(longest_lines[0], 1);
        cout<<temp->title;
        print_blank_space(longest_lines[1], strlen(temp->title));
        cout<<temp->ISBN;
        print_blank_space(longest_lines[2], strlen(temp->ISBN));
        cout<<temp->author;
        print_blank_space(longest_lines[3], strlen(temp->author));
        cout<<temp->date;
        print_blank_space(longest_lines[4], strlen(temp->date));
        cout<< temp->no_page;
        cout<<endl;     // Begin new line for the next data.
        temp = temp->next;
        }

    cout<<"\nTotal number of book registered: "<<cnt<<endl;

}


// helper funtion to change string to char. Eg, the title.
char* string_to_char(char* update_what , string update_to){
    int idx = 0;
    while (idx < update_to.length()){

        given_info[idx] = update_to[idx];
        idx ++;
    }
    given_info[idx] = '\0';

    return given_info; //strdup_(update_what);
}

/*  It first check which data the user want to change. It the updates.
    The return value type is bool that checks weather it is updated or not.*/
bool update(Node* book, char* update_what, string update_to){
    char *book_info;
    bool updated=true;

    if (strcmp(update_what, "title")==0){
        book->title = string_to_char(book->title, update_to);
        }
    else if (strcmp(update_what, "ISBN")==0){
        book->ISBN = string_to_char(book->ISBN, update_to);
        }
    else if (strcmp(update_what, "author")==0){
        book->author = string_to_char(book->author, update_to);
        }
    else if (strcmp(update_what, "date")==0){
        book->date = string_to_char(book->date,update_to);
        }
    else if (strcmp(update_what, "no_page")==0){
        book->no_page = string_to_char(book->no_page, update_to);
        }

    else{
        cout<<"Unrecognised keyword. Please input either of these keywords 'title', 'ISBN', 'author', 'date', 'no_page' on what you want to update."<<endl;
        updated=false;  // If the input key-word is not in the list, raise unupdated flag.
        return updated;
    }

    return updated;
}

// helper function to change string to char.
char* str_char(string s){
    int s_len = s.length();
    char* g;
    g = &s[0];
    g[s_len] = '\0';
    return g;
}
