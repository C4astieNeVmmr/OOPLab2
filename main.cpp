#include <iostream>
#include <cstring>
#include <time.h>

class Cstr {
public:
    char* str;
    int length;
    char* randomString(int length) {
        if (length <= 0) {
            return nullptr;
        }
        const char setOfChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        char* newString = new char[length + 1];
        for (int i = 0; i < length; i++) {
            newString[i] = setOfChars[rand() % ((sizeof(setOfChars) - 1))];
        }
        newString[length] = '\0';
        return newString;
    }
public:
    Cstr() {
        srand(time(NULL));
        int length = rand() % 21;
        this->length = length;
        this->str = randomString(length);
    }
    Cstr(const char* strAsChar) {
        this->length = strlen(strAsChar);
        this->str = new char[this->length + 1];
        strcpy(this->str, strAsChar);
    }
    Cstr(int length) {
        this->length = length;
        this->str = randomString(length);
    }
    Cstr(const Cstr& strToCopy) {//if by value(not reference), then new object in func will call copy constructor again, and copy contructors goes recursivly
        this->length = strToCopy.length;
        this->str = new char[strToCopy.length + 1];
        strcpy(this->str, strToCopy.str);
    }
    ~Cstr() {
        delete[] this->str;
    }

    Cstr operator=(Cstr strBuffer) {
        if (&strBuffer != this) {
            this->length = strBuffer.length;
            delete[] this->str;
            this->str = new char[this->length + 1];
            strcpy(this->str, strBuffer.str);
        }
        return *this;//* to dereference, and return actual object.
    }
    char& operator[](int index) {
        return this->str[index % this->length];
    }

    Cstr operator+(Cstr strB) {
        int newLength = this->length + strB.length;
        char* newStr = new char[newLength + 1];
        strcpy(newStr, this->str);
        strcat(newStr, strB.str);
        Cstr res(newStr);
        delete[] newStr;
        return res;
    }
    Cstr operator+=(Cstr strB) {
        *this = *this + strB;
        return *this;
    }
    bool operator==(Cstr strB) const {
        if (this->length != strB.length) {
            return false;
        }
        for (int i = 0; i < length; i++) {
            if (this->str[i] != strB.str[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator>(Cstr strB) {
        int i = 0;
        for (; i < this->length, i < strB.length; i++) {
            if (this->str[i] > strB.str[i]) {
                return 1;
            }
            if (this->str[i] < strB.str[i]) {
                return 0;
            }
        }
        return i == (this->length - 1);
    }
    bool operator<(Cstr strB) {
        return strB > *this;
    }
    friend std::ostream& operator<< (std::ostream& os, Cstr cstr) {
        os << cstr.str;
        return os;
    }
    friend std::istream& operator>> (std::istream& is, Cstr& cstr) {
        char buffer[100];
        is >> buffer;
        cstr = buffer;
        return is;
    }
    int getLength() {
        return this->length;
    }
};

bool isALongerB(Cstr strA,Cstr strB){
    return strA.getLength()>strB.getLength();
}
bool isAComesAfterB(Cstr strA,Cstr strB){
    return strA>strB;
}

class CstrArray{
    Cstr *data;
    int capacity;
    int len;//instead of size
    public:
    CstrArray(int l=1){
        this->data = new Cstr[l];
        this->len = 0;
        this->capacity = l;
    }
    ~CstrArray(){
        //delete[] data;
    }
    Cstr& operator[](int index){
        if(index>=this->len){
            throw std::out_of_range("");
        }
        return this->data[index];
    }
    CstrArray& operator+=(Cstr strA){
        if(this->capacity<=this->len){
            throw std::out_of_range("there is no capacity left");
        }
        this->data[++this->len-1] = strA;
        return *this;
    }
    void sort(bool(*op)(Cstr,Cstr)=isALongerB){
        for (int i=0;i<this->len-1;i++) {
            for (int j=0;j<this->len-i-1;j++) {
                if (op(this->data[j],this->data[j+1])){
                    Cstr buffer = this->data[j];
                    this->data[j]=this->data[j+1];
                    this->data[j+1]=buffer;
                }
            }
        }
    }
    bool isSorted(bool(*op)(Cstr,Cstr)=isALongerB){
        for(int i=0;i<(this->len)-1;i++){
            if(op(this->data[i],this->data[i+1])){
                return 0;
            }
        }
        return 1;
    }
    friend std::ostream& operator<<(std::ostream& os,CstrArray arr){
        for(int i=0;i<arr.len;i++){
            os << arr[i] << " ";
        }
        return os;
    }
    int getLength(){
        return this->len;
    }
    int getCapacity(){
        return this->capacity;
    }
};

int main(){
    CstrArray arr(10);
    Cstr str1("ABCD"),str2("LM"),str3("ZXC"),str4("AAAAA"),str5("QW");
    arr+=str1;
    arr+=str2;
    arr+=str3;
    arr+=str4;
    arr+=str5;
    std::cout << arr << "\t" << " is arr sorted - " << arr.isSorted(isALongerB) << "\n\n";
    arr.sort();//sort by Cstr length
    std::cout << arr << "\t" << " is arr sorted - " << arr.isSorted() << "\n\n";
    std::cout << "\n";
    arr.sort(isAComesAfterB);//sort by Cstr value
    std::cout << arr << "\t" << " is arr sorted - " << arr.isSorted(isAComesAfterB) << "\n\n";
    return 0;
}