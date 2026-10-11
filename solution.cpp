#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct Point {
    int x, y;
    
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

// Optimized version with early termination and better cache locality
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    
    // Sort by x-coordinate
    sort(points.begin(), points.end());
    
    long long result = 0;
    
    // For each pair of points where one can be bottom-left and other top-right
    for (int i = 0; i < n; i++) {
        // Early termination: if remaining points are too few, break
        if (n - i <= 1) break;
        
        for (int j = i + 1; j < n; j++) {
            // Quick check: if y condition fails, continue
            if (points[i].y >= points[j].y) continue;
            
            // Check if points[i] can be bottom-left and points[j] can be top-right
            // (x condition is already satisfied by sorting)
            
            bool has_point_inside = false;
            
            // Check if there's any point with x between points[i].x and points[j].x
            // and y between points[i].y and points[j].y
            for (int k = i + 1; k < j; k++) {
                if (points[k].y > points[i].y && points[k].y < points[j].y) {
                    has_point_inside = true;
                    break;
                }
            }
            
            if (!has_point_inside) {
                result++;
            }
        }
    }
    
    cout << result << endl;
    
    return 0;
}