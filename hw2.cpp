/// CIS22C-HM2B : This single file will contain all the code for Homework2. Program execution begins and ends here (in main).//
using namespace std;
#include <iostream>
#include <fstream>
/*
The following code file is divided into 4 sections
1. The interface and code for Class Student (supplied)
2. The interface and code for class StudentEsa (insert your HM1
code here)
3. The interface and code for class StudentDQI (The interface is
supplied. HM2 is writing the code to implement this interface)
4. The HM2 test program code (supplied)
*/
// 1. ************************ class Student code included here***************************
class Student
{ // A VERY simple Student consisting only of the student's ID and Name
    // Both the interface and the code will be located here.
private:
    int sid;      // Student ID
    string sname; // Full Name (Ex: KleinmanRon)
public:
    Student()
    { // Default constructor
        sid = 0;
        sname.clear();
    };
    Student(const Student &os)
    { // Copy constructor - overwrite internal variables
        sid = os.sid;
        sname = os.sname;
    };
    Student(int id, string name)
    { // Initializer Constructor - set internal variables
            sid = id;
        sname = name;
    };
    ~Student()
    { // Default Destructor - clear string
        sname.clear();
    };
    // Getters
    string getName() { return (sname); };
    int getId() { return (sid); };
};
// ********************** End class Student***************************************
// 2. ********************** Insert "class StudentEsa" code from your homework 1 assignment here

class StudentEsa
{
    //My name is sir Daniel Kuvanychbekov

    private: // Define whatever additional private variables you need
        Student* *sap; // Underlying pointer to array of Student pointers, which you will allocate
        Student* *tp; // Optionally used in realloc
        int cnum; // Number of students currently in array
        int cmz; // Current Max size of the array (may need to be expanded)
    
    public: // Publically supported methods YOU NEED TO IMPLEMENT. Replace each declaration with complete code
    
    // **************** Constructors / Destructor
    
        StudentEsa (int ms)
        {
            cmz = ms;
            sap = new Student* [cmz];
            cnum = 0;
            tp = NULL;
        } // 1. Normal Constructor. Create ESA of this size. May need to be resized later
        // *** The code for this might look like:
        //
        // StudentEsa(int ms) { // Allocate Enhanced Student Array capable of holding this many Student Ptrs
        // sap = new Student* [cmz = ms]; // sap points to an array of Student pointers of size cmz
        // cnum = 0; tp = NULL; // Initialize with no pointers currently in array
        // }
        //StudentEsa (); // 2. Default Constructor <Comment out, or use some predefined size, and EXPLAIN YOUR CHOICE>
        StudentEsa (StudentEsa& sep) // 3. Copy Constructor (what gets copied and what does not?)
        {
            cmz = sep.cmz;//we need to copy basically everything except tp
            cnum = sep.cnum;
            sap = new Student*[cmz];//I asked AI is my code correct and then why do we need to allocate it like this.
            for(int i = 0; i < cmz-1; i++)
            {
                sap[i] = sep.sap[i];
                //Also chat GPT said that this line should look like this ==>, but I'm not sure: "sap[i] = new Student(*(sep.sap[i]));  // Properly copy each Student object"
                // sap[i] = new Student(*(sep.sap[i]));
            }
        }
        ~StudentEsa(){ // 4. Default destructor (what gets freedup and what does not?){
            // for (int i = 0; i < cnum; i++) {//Chat GPT helped me with this, at first I just used line 85, didn't know that we need to also delete every element
                // delete sap[i]; // Delete each Student object
            // }
            delete[] sap;//Everything dynamically allocated
        }
        
        // ******************* Remaining public functions of the Extended Student Array
        
        // 1. Return the number of Students in the Collection
        int getSize(){
            return cnum;
        }
        
        // 2. GET: Get and return the ptr to the Student at the specified Array Index
        // Error if the supplied index >= number of entries. Return a NULL ptr
        Student* get(int index)
        {
            if(index > cnum-1 || index < 0){
                return nullptr;
            }else{
                return sap[index];
            }
        }
        // *** The code for this might look like:
        // Student* get (int idx) {
        // if ((idx<0) || (idx>=cnum)) return (NULL); // Bad index
        // return (sap[idx]); // Otherwise return Student ptr at that index in the array
        // }
        
        // 3. SET: Replace whatever is at the supplied index with the new Student ptr. Return index # on success
        // Error if the supplied index >= number of entries. Return -1
        // <DO NOT Destruct the Student whose ptr is at the supplied index>
        //
        int set(Student* newStudent, int index)
        {
            if(index > cnum-1 || index < 0){
                return -1;
            }else{
                sap[index] = newStudent;
                return index;
            }
        }
        
        // 4. INSERT: Insert Student ptr at the supplied index, by first "pushing back" every subsequent element
        // Error if the supplied index > number of entries. Return -1
        // OK if supplied index == number of entries (equivalent to an append)
        // Note: ESA size increases which may force a reallocation of the array. Return index # on success
        int insert(Student* nsp, int index)
        {
            if(index > cmz || index < 0){
                return -1;
            }else{
                //Need to add check for if cnum == cmz and if true than create a new array and then copy everything, need to delete old array before assigning to a newly bigger created 
                if(cnum == cmz)
                {
                    cmz = cmz * 2;
                    tp = new Student*[cmz];
                    for(int i = 0; i < cnum; i++){
                        tp[i] = sap[i];
                    }
                    delete[] sap;
                    sap = tp;
                }

                for(int i = cnum-1; i >= index; i--) //Here we start from the last element because if we start from the given index then we will lose data of the element at some point, so in order to not to lose it we need to copy to the empty element first
                {
                    sap[i+1] = sap[i];
                }

                sap[index] = nsp;

                cnum++;

                return index;
            }
        }
        
        // 5. REMOVE: Delete specified array element by "pulling forward" every subsequent element
        // Error if the supplied index >= number of entries. Return -1. Else decrement ESA size and return i
        // Note: <DO NOT Destruct the Student whose ptr is at the supplied index>
        int remove(int index)
        {
            int i;
            if(index > cnum || index < 0)
            {
                return -1;
            }
            else{
                sap[index] = nullptr; //I am not sure if I should make the pointer pointer to null but I guess it is not gonna harm the code
                
                for(i = index; i < cnum-1; i++)//I wrote the whole code and then asked chatGPT can it see any issues and he pointed that I made a mistake at "i < cnum" and it supposed to be "i < cnum-1" and I understood why
                {
                    sap[i] = sap[i+1];//assigns to the element which is forward               
                }
                cnum--;
                return i;
            }
        }
        
        // 6. APPEND: Append the ptr to the supplied Student to back of the ESA, bump ESA size
        // Return index # of new entry on success, -1 on failure
        // Note: This may force a reallocation of the array.
        int append(Student* nsp)
        {        
            if(cnum == cmz)
            {
                cmz = cmz * 2;
                tp = new Student*[cmz];
                for(int i = 0; i < cnum; i++){
                    tp[i] = sap[i];
                }
                delete[] sap;
                sap = tp;
            }   
            sap[cnum] = nsp;
            int ret = cnum - 1;
            cnum++;
            return ret;
        }
        
        
        // 7. PREPEND: Prepend the ptr to the supplied Student to the front of the ESA, increment ESA size
        // Return 0 on success, -1 on failure
        // Note: This may force a reallocation of the array.
        int prepend(Student* nsp)
        {
            bool done = false;
            
            if(cnum == cmz)
            {
                cmz = cmz * 2;
                tp = new Student*[cmz];
                for(int i = 0; i < cnum; i++){
                    tp[i] = sap[i];
                }
                delete[] sap;
                sap = tp;
            }
            for(int i = cnum-1; i >= 0; i--){
                sap[i+1] = sap[i];
                (i==0) ? done=true : done=false;
            }

            if(!done){
                return -1;
            }

            sap[0] = nsp;
            cnum++;
            return 0;
            
        }
};

// ********************** End class StudentEsa******************************
// 3. *************************** Homework 2. insert the code for the StudentDQI into the StudentDQI interface below ***************
// class "StudentDQI <Homework #2 - wraps (embeds) Extended Student Array (ESA) so it is invisible to external users of this class
class StudentDQI
{
private:
    StudentEsa *soa; // Allocated Extended Student Array
    // These might be useful if your solution is for extra credit and positions the DQ in the MIDDLE of the Extended Array
    unsigned int top; // Index value 1 above highest OA element used
    unsigned int btm; // Index value 1 below lowest OA element used
public:
    StudentDQI(unsigned int initSize){// Create a DQ with this initial size
        soa = new StudentEsa(initSize);//Created ESA, I guess that is only thing we need to do here
    }
    StudentDQI(StudentDQI &copy){// Equate this to an existing DQ (can use private parts directly)
        soa = new StudentEsa(*(copy.soa));//I believe we need to create a new array like this

        top = copy.top;
        btm = copy.btm;
    } 
    ~StudentDQI(){// Destruct the DQI (free OA space)
        delete soa;//delete everything we dynamicly allocated
    } 
    int getSize(){          // Gets # elements (Student *) in the DQ
        return soa->getSize();//since we are wrapping ESA we can use its function to get cnum
    }   
    bool isEmpty(){        // True if no elements held (âpopâ will fail)
        return (soa->getSize() == 0);
    }   
    int pushFront(Student *pushFr){ // Prepend a new element to the front
        return soa->prepend(pushFr);
    } 
    Student *popFront(){   // Remove the first element and return it
        Student *temp = soa->get(0);//we need to get first element b4 we lose access to it

        soa->remove(0);

        return temp;
    }   
    Student *lookFront(){  // Return the first element but do not remove it
        return soa->get(0);
    }   
    int pushBack(Student *app){// Append a new element to the back
        return soa->append(app);
    }  
    Student *popBack(){    // Remove the last element and return it
        Student *temp = soa->get(soa->getSize()-1);//we need to get first element b4 we lose access to it

        soa->remove(soa->getSize()-1);

        return temp;
    }   
    Student *lookBack(){   // Return the last element but do not remove it
        return soa->get(soa->getSize()-1);//we need to get first element b4 we lose access to it

    }   
};
// **************************** End class StudentDQI ******************************
// 4. *********************** Start of StudentDQI Test Program Code ************
int main()
{                        // Redirect Input
    string infileName;   // Use if Input redirected
    string outfileName;  // Use if output redirected
    FILE **input = NULL; // Recovering Cin
    // Command File Record entries
    int ssize;    // Size of extended array
    int nops;     // # operations to perform
    char command; // Command (G,Z F,G,H B,C,D)
    // Not all of the following are present in each command (Default given)
    int num;                // Student ID Number (-1 default)
    string name;            // Student Name (XXXX default)
    StudentDQI *dqi = NULL; // Pointer to DeQue
    Student sc;             // A class to collect Students is generated
    int x = 0;              // Useful variables
    cout << "Use input file: ";
    cin >> infileName; // Get name of file containing input data
    cout << "Using input file " << infileName << endl << endl;
    // Create an input file stream to read supplied file
    std::ifstream inp;
    inp.open(infileName.c_str());
    if (!inp)
    {
        cerr << "Error: file " << infileName.c_str() << " could not be opened " << endl;
        exit(1);
    }
    // First line is array size and # commands to add, every subsequent line is one of:
    //
    // GetSize: S / -1 / -1
    // isEmpty: Z / -1 / -1
    //
    // PushFront: F / Student ID / Student Name
    // PopFront: G / -1 / -1
    // LookFront : H / -1 / -1
    //
    // PushBack: B / Student ID / Student Name
    // PopBack: C / -1 / -1
    // LookBack : D / -1 / -1
    // Get Size of Extended Array and # of commands
    // ssize is size of extended array, nops is # commands
    inp >> ssize >> nops;
    cout << "Read Array size " << ssize << " Read # commands " << nops << endl;
    Student *stud;               // Array to hold pointer of created student.
    dqi = new StudentDQI(ssize); // Create Dequeue of specified size.
    for (int i = 0; i < nops; i++)
    { // Process Commands
        //**************************************************************
        inp >> command;
        inp >> num;
        inp >> name;
        cout << "Command: " << command << " " << num << " " << name << endl;
        // Process each command
        switch (command)
        {         // Convert to command for Extended Array
        case 'S': // Get Size
            cout << "Size: " << dqi->getSize() << endl;
            break;
        case 'Z': // Check if Empty
            cout << "Empty : " << dqi->isEmpty() << endl;
            break;
        case 'F': // Push Front
            stud = new Student(num, name);
            (void)dqi->pushFront(stud);
            cout << "Pushed Front " << num << " " << name << endl;
            break;
        case 'G': // Pop Front
            stud = dqi->popFront();
            if (stud)
            { // Success
                cout << "Pop Front " << stud->getId() << " " << stud -> getName() << endl;
                delete (stud);
            }
            break;
        case 'H': // Look Front
            stud = dqi->lookFront();
            if (stud)
            { // Success ... don't delete Student
                cout << "Look Front " << stud->getId() << " " << stud -> getName() << endl;
            }
            break;
        case 'B': // Push Back
            stud = new Student(num, name);
            (void)dqi->pushBack(stud);
            cout << "Pushed Back " << num << " " << name << endl;
            break;
        case 'C': // Pop Back
            stud = dqi->popBack();
            if (stud)
            { // Success
                cout << "Pop Back " << stud->getId() << " " << stud->getName() << endl;
                delete (stud);
            }
            break;
        case 'D': // Look Back
            stud = dqi->lookBack();
            if (stud)
            { // Success ... don't delete Student
                cout << "Look Back " << stud->getId() << " " << stud->getName() << endl;
            }
            break;
        default:
            cout << "Illegal Command: " << command << endl;
        }
    }
    // Print out Current contents of extended array
    x = dqi->getSize(); // Get number of array elements
    cout << "------------------" << endl
         << "Start Popping from bottom "
         << x << " Elements queued" << endl
         << endl;
    while (stud = dqi->popBack())
    {
        cout << "Student: ID = " << stud->getId() << " Name = " << stud->getName() << endl;
    }
    return (0);
};
// ********************************** End of test code *************************************
