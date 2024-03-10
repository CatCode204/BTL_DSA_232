#include "main.hpp"

//CANG THANG VCL
template<typename T>
class List {
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
};

template<typename T> struct Node {
    T data;
    Node* next;
};

template<typename T> class MyList: public List<T> {
private:
    int _size;
    Node<T> *_head,*_tail;
public:
    MyList();
    MyList(const MyList<T>& other);
    ~MyList();
    MyList<T>& operator = (const MyList<T>& other);
    void push_back(T);
    void push_front(T);
    void insert(int,T);
    void remove(int);
    T& get(int) const;
    int length() const;
    void clear();
    void print() const;
    void reverse();
};

class Dataset {
private:
    List<List<int>*>* _data;
    List<std::string>* _title;
    int _numRows,_numCols;
public:
    Dataset();
    ~Dataset();
    Dataset(const Dataset& other);
    Dataset& operator=(const Dataset& other);
    bool loadFromCSV(const char* fileName);
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    void getShape(int& nRows, int& nCols) const;
    void columns() const;
    bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    List<List<int>*>* getData() const;
    friend class kNN;
    friend void train_test_split(Dataset& X, Dataset& y, double test_size, Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);
};

class kNN {
private:
    int k;
    Dataset _feature,_label;
public:
    kNN(int k = 5);
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);
};

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

struct Info {
    double distance;
    int tag;
    friend bool operator < (const Info &a,const Info &b);
};