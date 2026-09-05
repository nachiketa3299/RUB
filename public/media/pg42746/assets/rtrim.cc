string r_trim(string const &s) {
    auto sc(s);

    auto it = find_if(
      sc.rbegin(), sc.rend(), 
      [](auto c){ return !isspace(c); }
    ).base();
    
    sc.erase(it, sc.end());
    return sc;
}