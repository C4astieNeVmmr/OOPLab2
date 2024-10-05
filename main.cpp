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

class CstrArray{
    Cstr *data;
    int capacity;
    int len;//instead of size
    public:
    int& getLength(){
        return this->len;
    }
    int getCapacity(){
        return this->capacity;
    }
    CstrArray(int l=1){
        this->data = new Cstr[l];
        (*this).getLength()=0;
        this->capacity = l;
    }
    ~CstrArray(){
        //delete[] data;
    }
    Cstr& operator[](int index){
        if(index>=(*this).getLength()){
            throw std::out_of_range("");
        }
        return this->data[index];
    }
    CstrArray& operator+=(Cstr strA){
        if((*this).getCapacity()<=(*this).getLength()){
            throw std::out_of_range("there is no capacity left");
        }
        (*this)[++(*this).getLength()-1] = strA;
        return *this;
    }
    CstrArray& sort(){

    }
    bool isSorted(){

    }
    friend std::ostream& operator<<(std::ostream& os,CstrArray arr){
        for(int i=0;i<arr.getLength();i++){
            os << arr[i] << " ";
        }
        return os;
    }
};

int main(){
    CstrArray arr(10);
    Cstr str1("ABC"),str2("LMN"),str3("ZXC"),str4("AAA");
    arr+=str1;
    arr+=str2;
    arr+=str3;
    arr+=str4;
    std::cout << arr;
    return 0;
}