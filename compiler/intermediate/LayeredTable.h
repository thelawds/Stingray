
#ifndef COMPILER_LAYEREDTABLE_H
#define COMPILER_LAYEREDTABLE_H

#include <deque>
#include <string>
#include <unordered_map>

template <typename T> class LayeredTable {
  public:
    inline void pushLayer() { symbols.push_front(std::unordered_map<std::string, T *>()); }

    inline void popLayer() { symbols.pop_front(); }

    inline bool containsAtCurrentLayer(const std::string &name) {
        return !symbols.empty() && symbols[0].contains(name);
    }

    inline bool contains(const std::string &name) {
        for (auto &layer : symbols) {
            if (layer.contains(name)) {
                return true;
            }
        }

        return false;
    }

    inline void putAtCurrentLayer(const std::string &name, T *value) {
        if (symbols.empty()) {
            pushLayer();
        }

        symbols[0][name] = value;
    }

    inline T *&operator[](const std::string &name) {
        for (auto &layer : symbols) {
            if (layer.contains(name)) {
                return layer[name];
            }
        }

        putAtCurrentLayer(name, nullptr);
        return symbols[0][name];
    }

  private:
    // works from right to left, which means that front() is current layer and back() is the farthest layer
    std::deque<std::unordered_map<std::string, T *>> symbols;
};

#endif // COMPILER_LAYEREDTABLE_H
