#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <ctime>
#include <iomanip>
#include <algorithm>
using namespace std;

class Node {
public:
    int val;
    int ckIn;
    int indCk;

    Node(int v, int ci, int ii) : val(v), ckIn(ci), indCk(ii) {}

    bool operator>(const Node& other) const {
        return val > other.val;
    }
};
class MinHeap {
private:
    vector<Node> heap;

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < heap.size() && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }

        if (rightChild < heap.size() && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index] > heap[parentIndex]) {
                swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    

public:
    void pop() {
        heap.front() = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }
    bool empty() const {
        return heap.empty();
    }
    Node top() const {
        return heap.front();
    }

    void push(const Node& node) {
        heap.push_back(node);
        heapifyUp(heap.size() - 1);
    }


};

void mergeSort(vector<string>& tempFiles, const string& outputFile) {
    int k = tempFiles.size();


    vector<ifstream> fileStreams;
    for (int i = 0; i < k; ++i) {
        fileStreams.emplace_back(tempFiles[i]);
    }

 
    ofstream outputFileStream(outputFile);

    
    MinHeap mh;

    for (int i = 0; i < k; ++i) {
        int val;
        if (fileStreams[i] >> val) {
            mh.push(Node(val, i, 0));
        }
    }

    while (!mh.empty()) {
        Node top = mh.top();
        mh.pop();
        outputFileStream << top.val << " ";
        int nextval;
        if (fileStreams[top.ckIn] >> nextval) {
            mh.push(Node(nextval, top.ckIn, top.indCk + 1));
        }
    }
    for (int i = 0; i < k; ++i) {
        fileStreams[i].close();
    }
    outputFileStream.close();
}

void externalSort(const string& inputFile, const string& outputFile) {
    ifstream inputStream(inputFile);

    vector<string> tempFiles;
    int chunkSize = 100000;  
    int fileIndex = 0;
    clock_t start = clock();

    while (!inputStream.eof()) {
        vector<int> chunk;

        for (int i = 0; i < chunkSize; ++i) {
            int val;
            if(inputStream.eof())
            {
                break;
            }
            if (inputStream >> val) {
                chunk.push_back(val);
            }
        }

  
        sort(chunk.begin(), chunk.end());

        string tempFileName = "temp" + to_string(fileIndex) + ".txt";
        ofstream tempFile(tempFileName);
        for (int val : chunk) {
            tempFile << val << "\n";
        }
        tempFile.close();

        tempFiles.push_back(tempFileName);
        fileIndex++;
    }

    mergeSort(tempFiles, outputFile);

    clock_t end = clock();
    double totalTime = double(end - start) / CLOCKS_PER_SEC;

    cout << "Number of integers in a temporary file: " << chunkSize << endl;
    cout << "Number of temporary files created" << fileIndex << endl;
    cout << "otal time taken by the program up to 2 decimal places " << fixed << setprecision(2) << totalTime << " seconds" << endl;

  
    for (const string& tempFile : tempFiles) {
        remove(tempFile.c_str());
    }

    inputStream.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " inputfilepath  outputfilepath" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    externalSort(inputFile, outputFile);

    return 0;
}
