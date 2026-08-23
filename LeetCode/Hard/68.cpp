class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result, currLine;
        int currLineLen = 0;
        for (int i = 0; i < words.size(); ++i) {
            // Adds word
            currLine.push_back(words[i]);
            currLineLen += words[i].size();

            // Places line
            if (i == words.size() - 1) {
                ostringstream stream;
                for (int j = 0; j < currLine.size(); ++j) {
                    stream << currLine[j];
                    if (j < currLine.size() - 1) {
                        stream << ' ';
                        currLineLen += 1;
                    }
                }
                while (currLineLen < maxWidth) {
                    currLineLen += 1;
                    stream << ' ';
                }

                result.push_back(stream.str());
            } else if (
                words[i + 1].size() + currLineLen + currLine.size() > maxWidth
            ) {
                // Builds line
                ostringstream stream;
                if (currLine.size() == 1) {
                    string word = currLine[0];
                    stream << word;
                    for (int j = word.size(); j < maxWidth; ++j) {
                        stream << ' ';
                    }
                } else {
                    int totalSpaces = maxWidth - currLineLen;
                    int numGaps = currLine.size() - 1;
                    int baseSpaces = totalSpaces / numGaps, numAdditional = totalSpaces % numGaps;
                    for (int j = 0; j < currLine.size(); ++j) {
                        stream << currLine[j];
                        
                        if (j != currLine.size() - 1) {
                            for (int k = 0; k < baseSpaces; ++k) {
                                stream << ' ';
                            }

                            if (j < numAdditional) {
                                stream << ' ';
                            }
                        }
                    }
                }

                // Places line onto justified text
                result.push_back(stream.str());

                // Cleans up line
                currLine.clear();
                currLineLen = 0;
            }
        }
        return result;
    }
};
