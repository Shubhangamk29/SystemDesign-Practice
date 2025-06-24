class MovieRentingSystem {
public:
    set<pair<int, pair<int, int>>> rented; //set of [price, [shop, movie]]
    vector<set<pair<int, int>>> available; //vector(indices are movie id) of set of [price, shop]
    vector<map<int, int>> prices; //vector(indices are movie id) of map of [movie, shop] -> price
    
    //[shopi, moviei, pricei]
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        available.resize(1e4 + 1);
        prices.resize(1e4 + 1);
        for(int i = 0; i < entries.size(); i++) {
            int p = entries[i][2], shop = entries[i][0], movie = entries[i][1];
            prices[movie][shop] = p;
            available[movie].insert({p, shop});
        }
    }
    
    vector<int> search(int movie) {
        vector<int> res;
        int count = 0;
        for(auto i : available[movie]) {
            count++;
            res.push_back(i.second);
            if(count == 5) break;
        }
        return res;
    }
    
    void rent(int shop, int movie) {
        int p = prices[movie][shop];
        available[movie].erase({p, shop});
        rented.insert({p, {shop, movie}});
    }
    
    void drop(int shop, int movie) {
        int p = prices[movie][shop];
        rented.erase({p, {shop, movie}});
        available[movie].insert({p, shop});
    }
    
    vector<vector<int>> report() {
        vector<vector<int>> res;
        int count = 0;
        for(auto i : rented) {
            res.push_back({i.second.first, i.second.second});
            count++;
            if(count == 5) break;
        }
        return res;
    }
};
