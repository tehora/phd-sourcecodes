int N, M;

// vector<int> ids;

struct edge {int a, b, t; bool invalid; };

vector<edge> edges;

// map<pair<int, int>, int> dane;

void czytgraf(const char *fname, int t) {
  FILE *f = fopen(fname, "rt");
  while(!feof(f)) {
    int a=-1, b=-1;
    fscanf(f, "%d;%d", &a, &b);
    if(a == -1) break;
    edges.emplace_back(edge{a, b, t, false});
    }                     
  fclose(f);
  }

void renumer() {
/*set<int> nry;
  map<int, int> numery;
  for(auto e: edges) nry.insert(e.a), nry.insert(e.b);
  N = 0;
  for(int nn: nry) numery[nn] = N++;
  for(auto& e: edges) e.a = numery[e.a], e.b = numery[e.b];
  M = edges.size();*/
  int min_id = 1000000000;
  for(auto e: edges) min_id = min(min_id, min(e.a, e.b));
  for(auto e: edges) e.a -= min_id, e.b -= min_id;
  int max_id = 0;
  for(auto e: edges) max_id = max(max_id, max(e.a, e.b));
  max_id++;
  
  vector<int> numery(max_id, 0);
  
  for(auto e: edges) numery[e.a] = numery[e.b] = 1;

  N = 0;
  for(int& x: numery) tie(x, N) = make_pair(N, N+x);

  for(auto& e: edges) e.a = numery[e.a], e.b = numery[e.b];
  M = edges.size();
  }
  
  
  
