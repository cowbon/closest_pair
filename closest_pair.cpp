#include<iostream>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<ctime>
#include<climits>
#include<thread>
#include<mutex>
using namespace std;

//test cases
const int num[5] = {100,151,1024,static_cast<int>(pow(2,14)),static_cast<int>(pow(2,16))};
const int max_num = pow(2,9);

//define a 2D point(X-coordinate,Y-coordinate)
struct point2d{
    int x,y;
    point2d(int x,int y):x(x),y(y){}
};

bool func(point2d a,point2d b){
    if(a.y == b.y) return (a.x < b.x);
    else return (a.y < b.y);
}

//sort by X coordinate
bool func2(point2d a,point2d b){
    return (a.x < b.x);
}

//sort by Y coordinate
bool func3(point2d a,point2d b){
    return (a.y < b.y);
}

long dist(point2d& a,point2d& b){
   return pow((b.x-a.x),2)+pow((b.y-a.y),2);
}

//Brutal-force algorithm
//Calculate the distance between one point and all of the other points
clock_t brutal(vector<point2d>& vec){
    clock_t time = clock();
    long min = dist(vec[0],vec[1]);
    for(int i = 0;i < vec.size();i++){
	for(int j = i+1; j < vec.size();j++){
	    long dis = dist(vec[i],vec[j]);
	    if(dis < min) min = dis;
	}
    }
    cout<<"Closest distance: "<<sqrt(min)<<endl;
    return clock()-time;
}

//random number generator
void num_gen(vector<point2d>& vec,int n){
    while(vec.size() < n){
	int x = rand() % max_num;
	int y = rand() % max_num;
	bool add = true;

	//prevent duplicate point
	for(int i = 0;i < vec.size();i++){
	    if(vec[i].x == x && vec[i].y == y){
		add=false;
		break;
	    }
	}
	if(add){
	    point2d point(x,y);
	    vec.push_back(point);
	}
    }
}

//Divide and conquer
long divide(vector<point2d>& vec,int left,int right){
    if(left>=right) return LONG_MAX;
    int mid = (left+right)/2;
    long min_d = min(divide(vec,left,mid),divide(vec,mid+1,right)); //recursively

    vector<point2d> tmp;
    for(int i=mid;i>=left&&vec[mid].x-vec[i].x<min_d;--i)
	tmp.push_back(vec[i]);
    for(int i=mid+1;i<=right&&vec[i].x-vec[mid].x<min_d;++i)
	tmp.push_back(vec[i]);

    sort(tmp.begin(),tmp.end(),func3);

    for(int i = 0;i<tmp.size()-1;++i){
	for(int j = 1;j<=3&&i+j<tmp.size();++j){
	    long d=dist(tmp[i],tmp[i+j]);
	    min_d = min(min_d,d);
	}
    }
    return min_d;
}

//Start the counter
clock_t divide_and_conquer(vector<point2d>& vec){
    clock_t time = clock();
    sort(vec.begin(),vec.end(),func2);
    cout<<"Closest distance: "<<sqrt(divide(vec,0,vec.size()-1))<<endl;
    return clock()-time;
}

void test1(vector<point2d>& point){
    clock_t time = brutal(point);
    cout<<"Time for brutal force algorithm: "<<time<<endl;
}

void test2(vector<point2d>& point){
    clock_t time2 = divide_and_conquer(point);
    cout<<"Time for divide-and-conquer algorithm: "<<time2<<endl;
}

void test(int i){
    cout<<"Case "<<i+1<<": "<<num[i]<<" point(s)"<<endl;
    vector<point2d> point;
    num_gen(point,num[i]);
    vector<point2d> pot = point;
    thread t1(test1,ref(point));
    thread t2(test2,ref(pot));
    t1.join();
    t2.join();
    cout<<endl;
}

int main(){
    srand(0);
    //thread th[5];
    for(int i=0;i<5;i++)
	test(i);

    return 0;
} 

