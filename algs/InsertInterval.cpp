/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
#include <iostream>
#include <vector>
using namespace std;

struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int len = intervals.size();
        vector<Interval> result;
        if( len == 0 ) {
            result.push_back(newInterval);
            return result;
        }
        int s = 0, e = len-1, mid = 0;
        int ns = newInterval.start, ne = newInterval.end;
        if( ns > intervals[e].end ) {
            intervals.push_back(newInterval);
            return intervals;
        }
        if( ne < intervals[0].start ) {
            intervals.insert(intervals.begin(), newInterval);
            return intervals;
        }
        while( s <= e ) {
            mid = (s+e)/2;
            if( intervals[mid].end == ns ) {
                break;
            } else if( intervals[mid].end > ns ) {
                if( mid > 0 && intervals[mid-1].end < ns ) {
                    mid--;
                    break;
                }
                e = mid - 1;
            } else {
                if( mid < e && intervals[mid+1].end > ns ) {
                    mid++;
                    break;
                }
                s = mid + 1;
            }
        }
        int ms = mid;
        s = 0;
        e = len - 1;
        while( s <= e ) {
            mid = (s+e)/2;
            if( intervals[mid].start == ne ) {
                break;
            } else if( intervals[mid].start > ne ) {
                if( mid > 0 && intervals[mid-1].start < ne ) {
                    mid--;
                    break;
                }
                e = mid - 1;
            } else {
                if( mid < e && intervals[mid+1].start > ne ) {
                    mid++;
                    break;
                }
                s = mid + 1;
            }
        }
        int me = mid;
        if( ms > me ) return intervals;
        if( intervals[ms].end < newInterval.start ) {
            s = (intervals[ms+1].start < newInterval.start) ? intervals[ms+1].start : newInterval.start;
            ms++;
        } else {
            s = (intervals[ms].start < newInterval.start) ? intervals[ms].start : newInterval.start;
        }
        if( intervals[me].start > newInterval.end ) {
            e = (intervals[me-1].end > newInterval.end) ? intervals[me-1].end : newInterval.end;
            me--;
        } else {
            e = (intervals[me].end > newInterval.end) ? intervals[me].end : newInterval.end;
        }
        int i = -1;
        vector<Interval>::iterator insert;
        for( vector<Interval>::iterator it = intervals.begin(); it != intervals.end(); ++it ) {
            i++;
            if( i == ms ) {
                result.push_back(*(new Interval(s,e)));
            }
            if( i >= ms && i <= me ) continue;
            result.push_back(*it);
        }
        return result;
    }
};
int main() {
	Solution solution;
	vector<Interval> input;
	Interval *i1 = new Interval(2,4);
	input.push_back(*i1);
	i1 = new Interval(5,7);
	input.push_back(*i1);
	i1 = new Interval(8,10);
	input.push_back(*i1);
	i1 = new Interval(11,13);
	input.push_back(*i1);
	Interval *newInterval = new Interval(3,6);
	vector<Interval> result = solution.insert(input, *newInterval);
	for( vector<Interval>::iterator it = result.begin(); it != result.end(); ++it ) {
		cout << it->start << "," << it->end << endl;
	}
	return 1;
}
