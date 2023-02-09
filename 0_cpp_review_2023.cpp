

// find an element from a string
int pos = line.find ("X");
if (pos != -1) count << line[pos];

//find a substring from the end
  std::string str ("The sixth sick sheik's sixth sheep's sick.");
  std::string key ("sixth");
  std::size_t found = str.rfind(key);  //index of the last ‘sixth’

// split a string into vector of words
    string s = "hello 123 234 world";
    stringstream ss(s);
    vector<string> v1;
    while(ss >> c) // stringstream is something like iostream cin
    {
       v1.push_back(c); 
    }
// digit string manipulations
// convert 23 to 5-digit palindrome
string p1 = ’234’
string p2 = p1;
reverse(p2.begin(), p2.end());
string palindrome = p1 + p2.substr(1); //“234” + “32” = “23432”
// convert string to long long or int
String a = “1234”
long long b = stol(a);
Int c = stoi(a);

# sort a string
string sortedWord = "yifeng";
sort(sortedWord.begin(), sortedWord.end()); //ascending order
sort(sortedWord.rbegin(), sortedWord.rend()); //descending order

# substring
string str1 = "yifeng";
string substr1 = str1.substr(1, 3); //“ife”
String substr2 = str1.substr(3); //remaining: eng


