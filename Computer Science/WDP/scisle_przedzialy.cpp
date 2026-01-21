#include<bits/stdc++.h>

using namespace std;

// template kolejki monotonicznej
template<typename T, typename Compare>
struct MonotonicDeque{
    deque<T> dq;
    Compare is_worse;
    void push(T val){
        while(!dq.empty() && is_worse(dq.back(), val)) dq.pop_back();
        dq.push_back(val);
    }
    T& front() { return dq.front(); }
    void pop_front() { dq.pop_front(); }
    bool empty() { return dq.empty(); }
    T& back() { return dq.back(); }
};

struct PointVal{
    long long val, idx;
};

struct Segment{
    int l, r;
    long long dx; // różnica x (xr - xl)
    long long len; // długość (r - l + 1)
};

// rozne komparatory (sortowanie rosnaca/malejaco/po jakosci przedzialow) 
struct RemoveSmaller{ 
    bool operator()(const PointVal& a, const PointVal& b) const { return a.val <= b.val; }
};

struct RemoveLarger { 
    bool operator()(const PointVal& a, const PointVal& b) const { return a.val >= b.val; }
};

struct RemoveWorseQuality {
    // porwunujemy kwadraty jakosci ale z racji zbyt duzych liczb robimy to na long doublach
    bool operator()(const Segment& a, const Segment& b) const {
        return (long double)a.dx * a.dx * b.len < (long double)b.dx * b.dx * a.len;
    }
};

int main(){
    int n; 
    long long U; 
    cin >> n >> U;
    
    vector<pair<long long, long long>> punkty(n);
    for(auto &[x, y] : punkty) cin >> x >> y;
    
    MonotonicDeque<PointVal, RemoveSmaller> MaxQ;
    MonotonicDeque<PointVal, RemoveLarger> MinQ;

    int left = 0;
    vector<int> longest(n);
    // dla kazdego i liczymy najdluzszy przedzial zgodny z warunkami zadania idacy w lewa strone
    for(int i = 0; i < n; i++){
        MaxQ.push({punkty[i].second, i});
        MinQ.push({punkty[i].second, i});
        
        while(!MaxQ.empty() && !MinQ.empty() && MaxQ.front().val - MinQ.front().val > U){
            left++;
            if(MaxQ.front().idx < left) MaxQ.pop_front();
            if(MinQ.front().idx < left) MinQ.pop_front();
        }
        longest[i] = i - left + 1;
    }
    
    //sprawdzamy ktore przedzialy sa kandydatami - ktore sa maksymalne
    vector<Segment> candidates;
    for(int i = 0; i < n; i++){
        if(i == n - 1 || longest[i + 1] != longest[i] + 1){ // jesli zachodzi warunek to kolejny pokrywa aktualny
            int r = i;
            int l = i - longest[i] + 1;
            
            long long dx = punkty[r].first - punkty[l].first;
            long long len = r - l + 1;
            
            candidates.push_back({l, r, dx, len});
        }
    }

    MonotonicDeque<Segment, RemoveWorseQuality> Q;
    int ptr = 0;
    for(int i = 0; i <  n; i++){ // dla kazdego punktu znajdujemy najlepszy przedzial ktory go zawiera
        // Dodajemy kandydatów
        while(ptr < (int)candidates.size() && candidates[ptr].l <= i){
            Q.push(candidates[ptr]);
            ptr++;
        }
        // Usuwamy nieaktywnych
        while(!Q.empty() && Q.front().r < i) Q.pop_front();
        
        if(!Q.empty()) {
            cout << Q.front().l + 1 << " " << Q.front().r + 1 << "\n";
        }
    }
    
    return 0;
}
