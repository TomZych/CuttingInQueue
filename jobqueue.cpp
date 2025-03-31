#include <iostream>
#include <cmath>
#include <functional>
#include <algorithm>

using namespace std;

class Job
{
private:
  std::string name;
  int priority;

public:
  Job(std::string n, int p) : name(n), priority(p) {}

  void execute()
  {
    std::cout << "Running the job with name "
              << name
              << " and priority "
              << priority << endl;
  }

  std::string getName()
  {
    return name;
  }

  int getPriority()
  {
    return priority;
  }

  bool operator>(const Job& other) const {
    return priority > other.priority;
  }
};


template <typename T, typename Compare = greater<T> >
class MaxHeap{
private:
    vector<T> heap;
    Compare greater_than;

    void upheap(int j){
        while (j > 0){
            int parent = (j-1)/2;
            if (greater_than(heap[j],heap[parent])){
                swap(heap[j], heap[parent]);
                j = parent;
            } else{
                break;
            }
        }
    }

    void downheap(int j){
        int size = heap.size();
        while (true){
            int left = 2*j +1;
            int right = 2*j +2;
            int largest = j;

            if (left < size && greater_than(heap[left], heap[largest])){
                largest = left;
            }
            if (right < size && greater_than(heap[right],heap[largest])){
                largest = right;
            }
            if (largest == j){
                break;
            }
            swap(heap[j], heap[largest]);
            j = largest;
        }

    }
public:

    void insert(const T& value){
        heap.push_back(value);
        upheap(heap.size()-1);
    }

    T getMax() {
        if (heap.empty()){
            throw runtime_error("Empty heap");
        }
        T maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        downheap(0);
        return maxVal;
    }

    bool isEmpty() const {
        return heap.empty();
    }

};

template <typename T>
class PriorityQueue{
private:
    MaxHeap<T> maxHeap;

public:
    void insert(const T& item){
        maxHeap.insert(item);
    }

    T getMax(){
        return maxHeap.getMax();
    }

    bool isEmpty() const {
        return maxHeap.isEmpty();
    }

};
class JobQueue{
private:
    PriorityQueue<Job> jobQueue;

public:
    void insert(Job job){
        jobQueue.insert(job);
    }

    void runHighestPriority(){
        if (jobQueue.isEmpty()){
            cout << "No jobs in queue. " << endl;
        }
        else {
            Job highestPriorityJob = jobQueue.getMax();
            highestPriorityJob.execute();
        }
    }

};


int main(){
    JobQueue jobQueue;
 
    Job jobA("job a", 5);
    Job jobB("job b", 2);
    Job jobC("job c", 9);
    Job jobD("job d", 8);
    Job jobE("job e", 1);
    jobQueue.insert(jobA);
    jobQueue.insert(jobB);
    jobQueue.insert(jobC);
    jobQueue.insert(jobD);
    jobQueue.insert(jobE);
    
    jobQueue.runHighestPriority(); // Calls jobC.execute() since job C has the highest priority
    jobQueue.runHighestPriority(); // Calls jobD.execute() since job C has the highest priority
    jobQueue.runHighestPriority(); // Calls jobA.execute() since job C has the highest priority
    jobQueue.runHighestPriority(); // Calls jobB.execute() since job C has the highest priority
    jobQueue.runHighestPriority(); // Calls job1.execute() since job C has the highest priority
}
