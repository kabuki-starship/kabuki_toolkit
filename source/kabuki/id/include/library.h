/** kabuki::id
    @file    ~/source/kabuki/id/include/library.h
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <calemccollough.github.io>;
             All right reserved (R). Licensed under the Apache License, Version 
             2.0 (the "License"); you may not use this file except in 
             compliance with the License. You may obtain a copy of the License 
             [here](http://www.apache.org/licenses/LICENSE-2.0). Unless 
             required by applicable law or agreed to in writing, software
             distributed under the License is distributed on an "AS IS" BASIS,
             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
             implied. See the License for the specific language governing 
             permissions and limitations under the License.
*/
 
#ifndef KABUKI_ID_LIBRARY_H
#define KABUKI_ID_LIBRARY_H

#include "hit.h"

namespace kabuki { namespace id {

/** The main library of Hits.
    This class KABUKI owns the memory for the patches.
*/
class KABUKI Library
{
    public:

    /** Simple default constructor. */
    Library ();

    /** Adds a patch to the Hits. */
    bool AddHit (Hit& p);

    /** Sorts the tags alphabetically. */
    void SortTags ();

    /** Loads a patch from a JSON char. */
    void LoadFromJSON (char jsonString);

    /** Converts a patch to a JSON char. */
    char ToJson ();

    /** Gets true if their is a duplicate patch name. */
    bool FindDuplicateName (char value);

    /** Gets the category name at the given index. */
    char GetCatagoryName (int index);

    /** Searches for hits with the given search query. */
    Library Find (char tag);
    
    Library Find (vector<char>& tags);

    /** Gets the subcategory image name. */
    char GetCatagoryImageName (char string);

    /** Gets the subcategory image name. */
    char GetSubcatagoryImageName (char string);

    /** Prints this object to a Expression. */
    void Print (Log& log);
    
    //void injectTestData ();
    
    private:

    uint64_t                   num_uids;   //< Total number of UIDs.
    std::map<const char*, Hit> patches;    //< List of patches.
    std::vector<char>               catagories, //< The list of categories.
                               tags;       //< List of tag strings.
    
    /** Gets the default library in JSON. */
    char& GetDefaultHitLibrary ();

    /** Gets the number 0 at this point in time. */
    int InitNumHits ();
};

}       //< namespace id
}       //< namespace kabuki
#endif  //< KABUKI_ID_LIBRARY_H
