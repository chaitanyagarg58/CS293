#ifndef PLANNER_H
#define PLANNER_H
#define INT_MAX 2147483647

#include <iostream>
#include <bits/stdc++.h>
#include <string>
using namespace std;

char *null = new char[32];

struct Journey
{
  // define suitable fields here
  string station_one = null, station_two; // station_one is our key
  float start_time, finish_time;
};

struct Query
{
  // define suitable fields here
  float time1, time2;
  string stop;
};

bool compare(Query a, Query b)
{
  return a.time1 < b.time1;
}

class Planner
{
  // define suitable fields here
private:
  int N;
  struct Journey *jour;

public:
  Planner(int n = 100)
  {
    N = n;
    jour = new Journey[N];
  }

  int hashValue(string key)
  {
    long p = 3, pow = 1;
    int hash = 0;
    for (int i = 0; i < key.length(); i++)
    {
      hash = (hash + (key[i] - 'A') * pow) % N;
      pow = pow * p;
    }
    return hash;
  }
  int findFreeIndex(string key)
  {
    int hash = hashValue(key);
    for (int i = hash; true; i = (i + 1) % N)
    {
      if (jour[i].station_one == null)
        return i;
      if (i == (hash - 1 + N) % N)
        return -1;
    }
  }
  bool add(struct Journey e)
  {
    int index = findFreeIndex(e.station_one);
    if (index == -1)
      return false;
    jour[index] = e;
    return true;
  }
  void query_station(string key, float time)
  {
    int j = 0, hash = hashValue(key);
    struct Query ans[N];
    bool found = false;
    for (int i = hash; true; i = (i + 1) % N)
    {
      if (jour[i].station_one == key && jour[i].start_time >= time)
      {
        ans[j].time1 = jour[i].start_time;
        ans[j++].stop = jour[i].station_two;
        // cout << jour[i].start_time << " " << jour[i].station_two << endl;
        found = true;
      }
      if (jour[i].station_one == null || i == (hash - 1 + N) % N)
      {
        if (!found)
          cout << "Station not Found." << endl;
        break;
      }
    }
    if (j == 0)
      return;
    sort(ans, ans + j, compare);
    for (int i = 0; i < j; i++)
      cout << ans[i].time1 << " " << ans[i].stop << endl;

    return;
  }
  void query_journey(string start, float time, string dest)
  {
    struct Query ans[N];
    int j = 0, hash = hashValue(start);
    train_nostop(start, time, dest, ans, j);

    for (int i = hash; true; i = (i + 1) % N)
    {
      if (jour[i].station_one == start && jour[i].station_two != dest && jour[i].start_time >= time)
      {
        float time2;
        time2 = train_exist(jour[i].station_two, jour[i].finish_time, dest, ans, j);
        if (time2 != INT_MAX)
        {
          ans[j].time1 = jour[i].start_time;
          ans[j].stop = jour[i].station_two;
          ans[j++].time2 = time2;
        }
      }
      if (jour[i].station_one == null || i == (hash - 1 + N) % N)
        break;
    }
    if (j == 0)
    {
      cout << "ERROR" << endl;
      return;
    }
    sort(ans, ans + j, compare);

    cout << ans[0].time1 << " ";
    if (ans[0].stop != "")
      cout << ans[0].stop << " " << ans[0].time2;
    cout << endl;
    return;
  }

  float train_exist(string start, float time, string end, struct Query *ans, int &j)
  {
    int hash = hashValue(start);
    float min = INT_MAX;
    for (int i = hash; true; i = (i + 1) % N)
    {
      if (jour[i].station_one == start && jour[i].station_two == end && jour[i].start_time >= time)
      {
        if (min > jour[i].start_time)
          min = jour[i].start_time;
      }
      if (jour[i].station_one == null || i == (hash - 1 + N) % N)
        return min;
    }
  }

  void train_nostop(string start, float time, string end, struct Query *ans, int &j)
  {
    int hash = hashValue(start);
    for (int i = hash; true; i = (i + 1) % N)
    {
      if (jour[i].station_one == start && jour[i].station_two == end && jour[i].start_time >= time)
        ans[j++].time1 = jour[i].start_time;
      if (jour[i].station_one == null || i == (hash - 1 + N) % N)
        return;
    }
    return;
  }
};

#endif