#include<iostream>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<ctime>
#include<climits>
using namespace std;

const int num[5] = {100,151,1024,pow(2,14),pow(2,16)};
const int max_num = pow(2,9);

struct point2d{
    int x,y;
    point2d(int x,int y):x(x),y(y){}
};

bool func(point2d a,point2d b){
    if(a.y == b.y) return (a.x < b.x);
    else return (a.y < b.y);
}

bool func2(point2d a,point2d b){
    return (a.x < b.x);
}

bool func3(point2d a,point2d b){
    return (a.y < b.y);
}

long dist(point2d& a,point2d& b){
   return pow((b.x-a.x),2)+pow((b.y-a.y),2);
}

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

void num_gen(vector<point2d>& vec,int n){
    while(vec.size() < n){
	int x = rand() % max_num;
	int y = rand() % max_num;
	bool add = true;
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

long divide(vector<point2d>& vec,int left,int right){
    if(left>=right) return LONG_MAX;
    int mid = (left+right)/2;
    long min_d = min(divide(vec,left,mid),divide(vec,mid+1,right));

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

clock_t divide_and_conquer(vector<point2d>& vec){
    clock_t time = clock();
    sort(vec.begin(),vec.end(),func2);
    cout<<"Closest distance: "<<sqrt(divide(vec,0,vec.size()-1))<<endl;
    return clock()-time;
}

int main(){
    srand(0);
    for(int i=0;i<5;i++){
	cout<<"Case "<<i+1<<": "<<num[i]<<" point(s)"<<endl;
	vector<point2d> point;
	num_gen(point,num[i]);
	cout<<"ok"<<endl;
	clock_t time = brutal(point);
	cout<<"Time for brutal force algorithm: "<<time<<endl;
	clock_t time2 = divide_and_conquer(point);
	cout<<"Time for divide-and-conquer algorithm: "<<time2<<endl<<endl;
    }

    return 0;
} 

