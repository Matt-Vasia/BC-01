#ifndef GEMINI_HASH_H
#define GEMINI_HASH_H

#include <string>
#include <vector>
#include <cstdint>

class GeminiHash256 {
public:
    std::string hash(const std::string& message);

private:
    uint32_t right_rotate(uint32_t n, int b);

    static const std::vector<uint32_t> _h;
    static const std::vector<uint32_t> _k;
};

#endif // GEMINI_HASH_H