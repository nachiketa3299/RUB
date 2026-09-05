string l_trim(string const &s) {
  auto sc(s);

  auto it = find_if(
    sc.begin(), sc.end(), 
    [](auto c){ return !isspace(c); }
  );

  sc.erase(sc.begin(), it);
  return sc;
}