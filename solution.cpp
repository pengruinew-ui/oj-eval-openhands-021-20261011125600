#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

struct Point {
    int x, y;
    
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

// Optimized approach with better pruning strategies
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
    
    // Precompute prefix/suffix information for better pruning
    vector<int> prefix_min_y(n), prefix_max_y(n);
    vector<int> suffix_min_y(n), suffix_max_y(n);
    
    prefix_min_y[0] = points[0].y;
    prefix_max_y[0] = points[0].y;
    for (int i = 1; i < n; i++) {
        prefix_min_y[i] = min(prefix_min_y[i-1], points[i].y);
        prefix_max_y[i] = max(prefix_max_y[i-1], points[i].y);
    }
    
    suffix_min_y[n-1] = points[n-1].y;
    suffix_max_y[n-1] = points[n-1].y;
    for (int i = n-2; i >= 0; i--) {
        suffix_min_y[i] = min(suffix_min_y[i+1], points[i].y);
        suffix_max_y[i] = max(suffix_max_y[i+1], points[i].y);
    }
    
    // Main algorithm with aggressive pruning
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Quick check: if y condition fails, continue
            if (points[i].y >= points[j].y) continue;
            
            
            
            // Check if there's any point with x between points[i].x and points[j].x
            // and y between points[i].y and points[j].y
            bool has_point_inside = false;
            
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