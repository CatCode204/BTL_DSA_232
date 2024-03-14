#include "kNN.hpp"

template<typename T> void Swap(T &a,T &b) {
    T c = a;
    a = b;
    b = c;
}
template<typename T> T Max(T a,T b) {
    return a > b ? a : b;
}
template<typename T> T Min(T a,T b) {
    return a < b ? a : b;
}
bool operator < (const Info &a,const Info &b) {
    return a.distance < b.distance;
}
template<typename T> void QuickSort(T* arr,int low,int high) {
    if (low >= high) return;
    Swap(arr[low],arr[high]);
    int j = low - 1;
    for (int i = low;i < high;++i)
        if (arr[i] < arr[high]) {
            Swap(arr[i],arr[++j]);
        }
    Swap(arr[++j],arr[high]);
    QuickSort(arr,low,j - 1);
    QuickSort(arr,j + 1,high);
}
double Distance(const MyList<int> *a,const MyList<int> *b) {
    double sum = 0;
    MyList<int>* aa = new MyList<int>(*a);
    MyList<int>* bb = new MyList<int>(*b);
    for (int i=0;i < a->length();++i) {
        sum += (aa->get(0) - bb->get(0)) * (aa->get(0) - bb->get(0));
        aa->remove(0);
        bb->remove(0);
    }
    delete aa;
    delete bb;
    return sqrt(sum);
}
template<typename T> MyList<T>::MyList() {
    this->_size = 0;
    this->_head = this->_tail = nullptr;
}
template<typename T> MyList<T>::MyList(const MyList<T>& other) {
    this->_tail = this->_head = nullptr;
    this->_size = 0;
    for (Node<T>* tmp = other._head;tmp != nullptr;tmp = tmp->next) {
        Node<T>* newNode = new Node<T>();
        newNode->data = tmp->data;
        newNode->next = nullptr;
        if (this->_head == nullptr)
            this->_head = this->_tail = newNode;
        else {
            this->_tail->next = newNode;
            this->_tail = newNode;
        } 
        this->_size++;
    }
}
template<typename T> MyList<T>::~MyList() {
    Node<T>* tmp = this->_head;
    while (tmp != nullptr) {
        Node<T>* shadow = tmp;
        tmp = tmp->next;
        delete shadow;
    }
    this->_head = this->_tail = nullptr;
    this->_size = 0;
}
template<typename T> MyList<T>& MyList<T>::operator=(const MyList<T>& other) {
    Node<T>* tmp = this->_head;
    while (tmp != nullptr) {
        Node<T>* shadow = tmp;
        tmp = tmp->next;
        delete shadow;
    }
    this->_head = this->_tail = nullptr;
    this->_size = 0;
    for (Node<T>* tmp = other._head; tmp != nullptr;tmp = tmp->next) {
        Node<T>* newNode = new Node<T>();
        newNode->data = tmp->data;
        newNode->next = nullptr;
        if (this->_head == nullptr) this->_head = this->_tail = newNode;
        else {
            this->_tail->next = newNode;
            this->_tail = newNode;
        }
        this->_size++;
    }
    return *this;
}
template<typename T> void MyList<T>::push_back(T value) {
    Node<T> *newNode = new Node<T>();
    newNode->data = value;
    newNode->next = nullptr;
    if (this->_head == nullptr)
        this->_head = this->_tail = newNode; 
    else {
        this->_tail->next = newNode;
        this->_tail = newNode;
    }
    this->_size++;
}
template<typename T> void MyList<T>::push_front(T value) {
    Node<T>* newNode = new Node<T>();
    newNode->data = value;
    newNode->next = this->_head;
    this->_head = newNode;
    if (this->_tail == nullptr) this->_tail = this->_head;
    this->_size++;
}
template<typename T> void MyList<T>::insert(int index,T value) {
    if (index < 0 || index > this->_size) return;
    if (index == 0) this->push_front(value);
    else if (index == this->_size) this->push_back(value);
    else {
        Node<T>* tmp = this->_head;
        for (int i=0;i < index - 1;++i) tmp = tmp->next;
        Node<T>* newNode = new Node<T>();
        newNode->data = value;
        newNode->next = tmp->next;
        tmp->next = newNode;
        this->_size++;
    }
}
template<typename T> void MyList<T>::remove(int index) {
    if (index < 0 || index >= this->_size) return;
    if (index == 0) {
        Node<T> *tmp = this->_head;
        this->_head = this->_head->next;
        delete tmp;
    } else {
        Node<T> *tmp = this->_head;
        for (int i=0;i < index - 1;++i) tmp = tmp->next;
        Node<T> *hold = tmp->next;
        tmp->next = hold->next;
        delete hold;
    }
    this->_size--;
    if (this->_size == 0) {
        delete this->_head;
        this->_tail = this->_head = nullptr;
    }
}
template<typename T> T& MyList<T>::get(int index) const {
    if (index < 0 || index >= this->_size) throw std::out_of_range("get(): Out of range");
    else {
        Node<T> *tmp = this->_head;
        for (int i=0;i < index;++i) tmp = tmp->next;
        return tmp->data;
    }
}
template<typename T> int MyList<T>::length() const {
    return this->_size;
}
template<typename T> void MyList<T>::clear() {
    while (this->_head != nullptr) {
        Node<T>* shadow = this->_head;
        this->_head = this->_head->next;
        delete shadow;
    }
    this->_tail = this->_head;
    this->_size = 0;
}
template<typename T> void MyList<T>::print() const {
    for (Node<T> *tmp = this->_head;tmp != nullptr; tmp = tmp->next) {
        std::cout << tmp->data;
        if (tmp->next != nullptr) std::cout << " ";
    }
    std::cout << std::endl;
}
template<typename T> void MyList<T>::reverse() {
    T* arr = new T[this->_size];
    Node<T> *tmp = this->_head;
    for (int i=0;i < this->_size;++i) {
        arr[i] = tmp->data;
        tmp = tmp->next;
    }
    for (int i=0;i < this->_size / 2;++i)
        Swap(arr[i],arr[this->_size - i - 1]);
    tmp = this->_head;
    for (int i=0;i < this->_size;++i) {
        tmp->data = arr[i];
        tmp = tmp->next;
    }
    delete arr;
}

Dataset::Dataset() {
    this->_numCols = this->_numRows = 0;
    this->_data = nullptr;
    this->_title = nullptr;
}
Dataset::~Dataset() {
    for (int i=0;i < this->_numRows;++i) {
        delete this->_data->get(0);
        this->_data->remove(0);
    }
    delete this->_data;
    delete this->_title;
    this->_data = nullptr;
    this->_title = nullptr;
    this->_numCols = this->_numRows = 0;
}
Dataset::Dataset(const Dataset& other) {
    this->_numRows = other._numRows;
    this->_numCols = other._numCols;
    this->_title = new MyList<std::string>(*(MyList<std::string>*)other._title);
    this->_data = new MyList<List<int>*>();
    MyList<List<int>*>* tmp = new MyList<List<int>*>(*(MyList<List<int>*>*)other._data);
    for (int i=0;i < this->_numRows;++i) {
        MyList<int>* newRow = new MyList<int>(*(MyList<int>*)tmp->get(0));
        tmp->remove(0);
        this->_data->push_back(newRow);
    }
    delete tmp;
}
Dataset& Dataset::operator = (const Dataset &other) {
    for (int i=0;i < this->_numRows;++i) {
        delete this->_data->get(0);
        this->_data->remove(0);
    }
    delete this->_data;
    delete this->_title;
    this->_numRows = other._numRows;
    this->_numCols = other._numCols;
    this->_title = new MyList<std::string>(*(MyList<std::string>*)other._title);
    this->_data = new MyList<List<int>*>();
    MyList<List<int>*>* tmp = new MyList<List<int>*>(*(MyList<List<int>*>*)other._data);
    for (int i=0;i < this->_numRows;++i) {
        MyList<int>* newRow = new MyList<int>(*(MyList<int>*)tmp->get(0));
        tmp->remove(0);
        this->_data->push_back(newRow);
    }
    delete tmp;
    return *this;
}
bool Dataset::loadFromCSV(const char* fileName) {
    std::ifstream inputStream(fileName);
    std::string input,token;
    std::stringstream ss;
    if (!std::getline(inputStream,input)) return false;
    ss.clear(); ss.str(input);
    MyList<std::string>* newTitle = new MyList<std::string>();
    while (getline(ss,token,',')) newTitle->push_back(token);
    int newNumCols = newTitle->length();
    List<List<int>*>* newData = new MyList<List<int>*>();
    int newNumRows = 0;
    while (std::getline(inputStream,input)) {
        ss.clear(); ss.str(input);
        MyList<int>* newDataRow = new MyList<int>();
        while (std::getline(ss,token,',')) newDataRow->push_back(std::stoi(token));
        if (newDataRow->length() != newNumCols) {
            delete newDataRow;
            for (int i=0;i < newNumRows;++i) {
                delete newData->get(0);
                newData->remove(0);
            }
            delete newData;
            delete newTitle;
            return false;
        }
        ++newNumRows;
        newData->push_back(newDataRow);
    }
    for (int i=0;i < this->_numRows;++i) {
        delete this->_data->get(0);
        this->_data->remove(0);
    }
    delete this->_data;
    delete this->_title;
    this->_numRows = newNumRows;
    this->_numCols = newNumCols;
    this->_title = newTitle;
    this->_data = newData;
    return true;
}
void Dataset::printHead(int nRows,int nCols) const {
    if (nRows < 0 || nCols < 0) return;
    nRows = Min(nRows,this->_numRows);
    nCols = Min(nCols,this->_numCols);
    MyList<std::string>* tmpTitle = new MyList<std::string>(*(MyList<std::string>*)this->_title);
    for (int i=0;i < nCols;++i) {
        std::cout << tmpTitle->get(0);
        if (i != nCols - 1) std::cout << " ";
        tmpTitle->remove(0);
    }
    delete tmpTitle;
    std::cout << endl;
    MyList<List<int>*>* tmpData = new MyList<List<int>*>(*(MyList<List<int>*>*)this->_data);
    for (int i=0;i < nRows;++i) {
        MyList<int>* tmpRow = new MyList<int>(*(MyList<int>*)tmpData->get(0));
        tmpData->remove(0);
        for (int j=0;j < nCols;++j) {
            std::cout << tmpRow->get(0);
            if (j != nCols - 1) std::cout << " ";
            tmpRow->remove(0);
        }
        delete tmpRow;
        if (i != nRows - 1) std::cout << std::endl;
    }
    delete tmpData;
}
void Dataset::printTail(int nRows,int nCols) const {
    if (nRows < 0 || nCols < 0) return;
    nRows = Min(nRows,this->_numRows);
    nCols = Min(nCols,this->_numCols);
    MyList<std::string>* tmpTitle = new MyList<std::string>(*(MyList<std::string>*)this->_title);
    for (int i=0;i < this->_numCols - nCols;++i) tmpTitle->remove(0);
    for (int i=0;i < nCols;++i) {
        std::cout << tmpTitle->get(0);
        if (i != nCols - 1) std::cout << " ";
        tmpTitle->remove(0);
    }
    delete tmpTitle;
    std::cout << std::endl;
    MyList<List<int>*>* tmpData = new MyList<List<int>*>(*(MyList<List<int>*>*)this->_data);
    for (int i = 0;i < this->_numRows - nRows;++i) tmpData->remove(0);
    for (int i = 0;i < nRows;++i) {
        MyList<int>* tmpRow = new MyList<int>(*(MyList<int>*)tmpData->get(0));
        tmpData->remove(0);
        for (int j = 0;j < this->_numCols - nCols;++j) tmpRow->remove(0);
        for (int j= 0;j < nCols;++j) {
            std::cout << tmpRow->get(0);
            if (j != nCols - 1) std::cout << " ";
            tmpRow->remove(0);
        }
        delete tmpRow;
        if (i != nRows - 1) std::cout << std::endl;
    }
    delete tmpData;
}
void Dataset::getShape(int &nRows,int &nCols) const {
    nRows = this->_numRows;
    nCols = this->_numCols;
}
void Dataset::columns() const {
    MyList<std::string>* tmpTitle = new MyList<std::string>(*(MyList<std::string>*)this->_title);
    for (int i=0;i < this->_numCols;++i) {
        std::cout << tmpTitle->get(0);
        tmpTitle->remove(0);
        if (i != this->_numCols - 1) std::cout << " ";
    }
    delete tmpTitle;
}
bool Dataset::drop(int axis,int index,std::string columnName) {
    if (axis != 0 || axis != 1) return false;
    if (axis == 0) {
        if (index < 0 || index >= this->_numRows) return false;
        delete this->_data->get(index);
        this->_data->remove(index);
        this->_numRows--;
        return true;
    }
    index = -1;
    MyList<std::string>* tmpTitle = new MyList<std::string>(*(MyList<std::string>*)this->_title);
    for (int i=0;i < this->_numCols;++i) {
        if (tmpTitle->get(0) == columnName) index = i;
        tmpTitle->remove(0);
    }
    delete tmpTitle;
    if (index == -1) return false;
    this->_title->remove(index);
    MyList<List<int>*>* tmpData = new MyList<List<int>*>(*(MyList<List<int>*>*)this->_data);
    for (int i=0;i < this->_numRows;++i) {
        tmpData->get(0)->remove(index);
        tmpData->remove(0);
    }
    delete tmpData;
    this->_numCols--;
    return true;
}
Dataset Dataset::extract(int startRow,int endRow,int startCol,int endCol) const {
    if (endRow == -1) endRow = this->_numRows - 1;
    if (endCol == -1) endCol = this->_numCols - 1;
    Dataset rt;
    rt._numRows = endRow - startRow + 1;
    rt._numCols = endCol - startCol + 1;
    rt._title = new MyList<std::string>();
    MyList<std::string>* tmpTitle = new MyList<std::string>(*(MyList<std::string>*)this->_title);
    for (int i=0;i < startCol;++i) tmpTitle->remove(0);
    for (int i=startCol;i <= endCol;++i) {
        rt._title->push_back(tmpTitle->get(0));
        tmpTitle->remove(0);
    }
    delete tmpTitle;
    rt._data = new MyList<List<int>*>();
    MyList<List<int>*>* tmpData = new MyList<List<int>*>(*(MyList<List<int>*>*)this->_data);
    for (int i=0;i < startRow;++i) tmpData->remove(0);
    for (int i=startRow;i <= endRow;++i) {
        MyList<int>* tmpRow = new MyList<int>(*(MyList<int>*)tmpData->get(0));
        MyList<int>* newRow = new MyList<int>();
        tmpData->remove(0);
        for (int j=0;j < startCol;++j) tmpRow->remove(0);
        for (int j=startCol;j <= endCol;++j) {
            newRow->push_back(tmpRow->get(0));
            tmpRow->remove(0);
        }
        delete tmpRow;
        rt._data->push_back(newRow);
    }
    delete tmpData;
    return rt;
}
List<List<int>*>* Dataset::getData() const {
    return this->_data;
}

kNN::kNN(int k) {
    this->k = k;
}
void kNN::fit(const Dataset& X_train, const Dataset& Y_train) {
    this->_feature = X_train;
    this->_label = Y_train;
}
Dataset kNN::predict(const Dataset& X_test) {
    Dataset rt;
    rt._numCols = 1;
    rt._numRows = X_test._numRows;
    rt._title = new MyList<std::string>();
    rt._title->push_back(this->_label._title->get(0));
    rt._data = new MyList<List<int>*>();
    MyList<List<int>*>* tmpLabel;
    MyList<List<int>*>* tmpFeature;
    MyList<List<int>*>* hold = new MyList<List<int>*>(*(MyList<List<int>*>*)X_test._data);
    Info arr[this->_feature._numRows];
    int cnt[10];
    for (int i=0;i < rt._numRows;++i) {
        tmpLabel = new MyList<List<int>*>(*(MyList<List<int>*>*)this->_label._data);
        tmpFeature = new MyList<List<int>*>(*(MyList<List<int>*>*)this->_feature._data);
        for (int j=0;j < this->_feature._numRows;++j) {
            arr[j].tag = tmpLabel->get(0)->get(0);
            tmpLabel->remove(0);
            arr[j].distance = Distance((MyList<int>*)tmpFeature->get(0),(MyList<int>*)hold->get(0));
            tmpFeature->remove(0);
        }
        hold->remove(0);
        delete tmpFeature;
        delete tmpLabel;
        QuickSort(arr,0,this->_feature._numRows);
        for (int j=0;j < 10;++j) cnt[j] = 0;
        for (int j=0;j < this->k;++j) cnt[arr[j].tag]++;
        int maxIndex = 0;
        for (int j=0;j < 10;++j)
            if (cnt[j] > cnt[maxIndex]) maxIndex = j;
        MyList<int>* newRow = new MyList<int>();
        newRow->push_back(maxIndex);
        rt._data->push_back(newRow);
    }
    delete hold;
    return rt;
}
double kNN::score(const Dataset& y_test,const Dataset& y_train) {
    int cnt = 0;
    MyList<List<int>*>* holdTest = new MyList<List<int>*>(*(MyList<List<int>*>*)y_test._data);
    MyList<List<int>*>* holdTrain = new MyList<List<int>*>(*(MyList<List<int>*>*)y_train._data);
    for (int i=0;i < y_test._numRows;++i) {
        if (holdTest->get(0)->get(0) == holdTrain->get(0)->get(0)) ++cnt;
        holdTest->remove(0);
        holdTrain->remove(0);
    }
    delete holdTest;
    delete holdTrain;
    return 1.0 * cnt / y_test._numRows;
}

void train_test_split(Dataset& X, Dataset& y, double test_size, Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test) {
    int numTest = std::ceil(test_size * X._data->length());
    X_train = X.extract(0,X._data->length() - numTest - 1);
    X_test = X.extract(X._data->length() - numTest);
    y_train = y.extract(0,X._data->length() - numTest - 1);
    y_test = y.extract(X._data->length() - numTest);
}