#ifndef SRC_Block_H
#define SRC_Block_H

#include <iostream>
#include <fstream>
#include <cstring>

const int sqn = 320;

class myString {
private:
    char s[68];
public:
    myString() = default;

    myString(const char *t) {
        int len = strlen(t);
        if (len > 64) exit(-1);
        for (int i = 0; i < len; ++i) {
            s[i] = t[i];
        }
    }

    ~myString() = default;

    friend bool operator<(const myString &x, const myString &y) { return (strcmp(x.s, y.s) < 0); }

    friend bool operator==(const myString &x, const myString &y) { return (!strcmp(x.s, y.s)); }
    
    friend bool operator<=(const myString &x, const myString &y) {
        return (x < y) || (x == y);
    }
    
    friend std::ostream &operator<<(std::ostream &x, const myString &y) {
        x << y.s;
        return x;
    }
};

template<class DataType>
struct Element {
    myString _index;
    DataType Data;
    Element() = default;

    Element(const DataType &t) {
        Data = t;
    }

    friend bool operator==(const Element<DataType> &a, const Element<DataType> &b) {
        return a.Data == b.Data;
    }

    friend bool operator<(const Element<DataType> &a, const Element<DataType> &b) {
        return (a.Data < b.Data);
    }

    friend bool operator>(const Element<DataType> &a, const Element<DataType> &b) {
        return !(a.Data < b.Data);
    }

    friend bool operator<=(const Element<DataType> &a, const Element<DataType> &b) {
        return !(a > b);
    }

    friend bool operator>=(const Element<DataType> &a, const Element<DataType> &b) {
        return !(a < b);
    }
};

template<class DataType>
struct Block {
    Element<DataType> mini, maxi;
    int nxt = -1;
    int size = 0;
    Element<DataType> ele[2 * sqn];
};

template<class DataType>
class database {
private:
    int nowsize = -1;
    std::fstream _file;
    std::string _filename;

    void read(int pos, Block<DataType> &blk) {
        _file.seekg(pos * sizeof(Block<DataType>)+sizeof(int));
        _file.read(reinterpret_cast<char *>(&blk), sizeof(blk));
    }

    void write(int pos, const Block<DataType> &blk) {
        _file.seekp(pos * sizeof(Block<DataType>)+sizeof(int));
        _file.write(reinterpret_cast<const char *>(&blk), sizeof(blk));
    }

    void read_compare(int pos, Block<DataType> &blk) {
        _file.seekg(pos * sizeof(Block<DataType>)+sizeof(int));
        _file.read(reinterpret_cast<char *>(&(blk.mini)), sizeof(blk.mini));
        _file.read(reinterpret_cast<char *>(&(blk.maxi)), sizeof(blk.maxi));
        _file.read(reinterpret_cast<char *>(&(blk.nxt)), sizeof(blk.nxt));
        _file.read(reinterpret_cast<char *>(&(blk.size)), sizeof(blk.size));
    }

    void split(int pos, Block<DataType> &blk) { // 裂块
        ++nowsize;
        static Block<DataType> cur;
        for (int i = sqn; i < blk.size; ++i) {
            cur.ele[i - sqn] = blk.ele[i];
        }
        cur.size = sqn + 1;
        cur.nxt = blk.nxt;
        blk.nxt = nowsize;
        blk.size = sqn;
        blk.mini = blk.ele[0];
        blk.maxi = blk.ele[blk.size - 1];
        cur.mini = cur.ele[0];
        cur.maxi = cur.ele[cur.size - 1];
        write(pos, blk);
        write(nowsize, cur);
    }

    void internal_insert(int pos, const Element<DataType> &ele) {
        static Block<DataType> cur;
        if (nowsize == -1) {
            ++nowsize;
            cur.size = 1;
            cur.mini = cur.maxi = ele;
            cur.ele[0] = ele;
            write(nowsize, cur);
            return;
        }
        read(pos, cur);
        int tmp = -1;
        for (int i = 0; i < cur.size; ++i) {
            if (ele < cur.ele[i]) {
                tmp = i;
                break;
            } else if (ele == cur.ele[i]) {
                return;
            }
        }
        if (tmp == -1) {
            ++cur.size;
            cur.ele[cur.size - 1] = ele;
        } else {
            ++cur.size;
            for (int i = cur.size - 1; i > tmp; --i) {
                cur.ele[i] = cur.ele[i - 1];
            }
            cur.ele[tmp] = ele;
        }
        if (cur.size > 2 * sqn) {
            split(pos, cur);
        } else {
            cur.mini = cur.ele[0];
            cur.maxi = cur.ele[cur.size - 1];
            write(pos, cur);
        }
    }

    void combine(int pos, Block<DataType> &blk) {
        int nx1 = blk.nxt;
        if (nx1 == -1) {
            write(pos, blk);
            return;
        }
        static Block<DataType> nx;
        read(nx1, nx);
        if (blk.size + nx.size <= 2 * sqn) {
            for (int i = blk.size; i < blk.size + nx.size; ++i) {
                blk.ele[i] = nx.ele[i - blk.size];
            }
            blk.size += nx.size;
            blk.nxt = nx.nxt;
            blk.mini = blk.ele[0];
            blk.maxi = blk.ele[blk.size - 1];
        }
        write(pos, blk);
    }

    void internal_delete(int pos, const Element<DataType> &ele) { // 确定块
        static Block<DataType> cur;
        read(pos, cur);
        for (int i = 0; i < cur.size; ++i) {
            if (cur.ele[i] > ele) break;
            if (cur.ele[i] == ele) {
                for (int j = i + 1; j < cur.size; ++j) {
                    cur.ele[j - 1] = cur.ele[j];
                }
                --cur.size;
                if (!cur.size) {
                    write(pos, cur);
                    break;
                }
                cur.mini = cur.ele[0];
                cur.maxi = cur.ele[cur.size - 1];
                if (cur.size < sqn) {
                    combine(pos, cur);
                } else {
                    write(pos, cur);
                }
                break;
            }
        }
    }

public:
    void setfile(std::string name) {
        _filename = name;
        _file.open(_filename);
        if (!_file) {
            _file.open(_filename, std::fstream::out);
            _file.close();
            _file.open(_filename);
            nowsize = -1;
            _file.seekp(0);
            _file.write(reinterpret_cast<char *>(&nowsize), sizeof(nowsize));
            _file.seekp(4);
            static Block<DataType> tmp;
            _file.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
        } else {
            _file.seekg(0);
            _file.read(reinterpret_cast<char *>(&nowsize), sizeof(nowsize));
        }
    }

    ~database() {
        _file.seekp(0);
        _file.write(reinterpret_cast<char *>(&nowsize), sizeof(nowsize));
        _file.close();
    }

    void insert(const Element<DataType> &ele) {
        static Block<DataType> cur;
        read_compare(0, cur);
        if (cur.size == 0 || ele < cur.mini) {
            internal_insert(0, ele);
            return;
        }
        static Block<DataType> nx;
        int i = 0;
        while (true) {
            if (cur.nxt == -1) {
                break;
            }
            read_compare(cur.nxt, nx);
            if (ele >= cur.mini && ele <= nx.mini) {
                if (ele == nx.mini) return;
                internal_insert(i, ele);
                return;
            }
            i = cur.nxt;
            cur = nx;
        }
        internal_insert(i, ele);
    }

    void del(const Element<DataType> &ele) {
        static Block<DataType> cur;
        int i = 0;
        while (i != -1) {
            read_compare(i, cur);
            if (cur.size == 0) {
                i = cur.nxt;
                continue;
            }
            if (cur.mini <= ele && cur.maxi >= ele) {
                internal_delete(i, ele);
                break;
            } else if (ele < cur.mini) {
                break;
            }
            i = cur.nxt;
        }
    }

    bool find(const myString &index) {
        static Block<DataType> cur;
        int i = 0;
        while (i != -1) {
            read_compare(i, cur);
            if (cur.size == 0) {
                i = cur.nxt;
                continue;
            }
            if ((cur.mini._index <= index) && (index <= cur.maxi.Data)) {
                read(i, cur);
                for (int j = 0; j < cur.size; ++j) {
                    if (cur.ele[j]._index == index) {
                        return true;
                    }
                }
            } else if (index < cur.mini._index) {
                break;
            }
            i = cur.nxt;
        }
         return false;
    }
    
    DataType find_value(const myString &index) {
        static Block<DataType> cur;
        int i = 0;
        while (i != -1) {
            read_compare(i, cur);
            if (cur.size == 0) {
                i = cur.nxt;
                continue;
            }
            if ((cur.mini._index <= index) && (index <= cur.maxi.Data)) {
                read(i, cur);
                for (int j = 0; j < cur.size; ++j) {
                    if (cur.ele[j]._index == index) {
                        return cur.ele[j];
                    }
                }
            } else if (index < cur.mini._index) {
                break;
            }
            i = cur.nxt;
        }
    }

    DataType modify(const myString &index) {
        static Block<DataType> cur;
        int i = 0;
        while (i != -1) {
            read_compare(i, cur);
            if (cur.size == 0) {
                i = cur.nxt;
                continue;
            }
            if ((cur.mini._index <= index) && (index <= cur.maxi.Data)) {
                read(i, cur);
                for (int j = 0; j < cur.size; ++j) {
                    if (cur.ele[j]._index == index) {
                        delete(cur.ele[j]);
                    }
                }
            } else if (index < cur.mini._index) {
                break;
            }
            i = cur.nxt;
        }
    }
};

#endif // SRC_Block_H
