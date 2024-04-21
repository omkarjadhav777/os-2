int lru(vector<int>& ref_str, int f)
// {
//     vector<int> recent(f);
//     unordered_set<int> tank;
//     int pgf=0;

//     for(int i=0;i<ref_str.size();i++)
//     {
//         if(tank.find(ref_str[i]) == tank.end())
//         {
//             pgf++;

//             if(tank.size()<f)
//             {
//                 tank.insert(ref_str[i]);
//                 recent.push_back(ref_str[i]);
//             }
//             else
//             {
//                 int pgreplace=recent.front();
//                 recent.erase(recent.begin());
//                 recent.push_back(ref_str[i]);
//                 tank.erase(pgreplace);
//                 tank.insert(ref_str[i]);


//             }    
            
            
//         }
//         else
//             {
//                 recent.erase(find(recent.begin(),recent.end(),ref_str[i]));
//                 recent.push_back(ref_str[i]);            
//             }
//     }

    
//     return pgf;
// }
