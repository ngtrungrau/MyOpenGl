#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include<Vertex.h>
namespace MyGl
{


    // ============================================================================
    // 1. Đọc file .ver (Vertices) truyền bằng tham chiếu &
    // ============================================================================
    inline void LoadVertexBuffer(const std::string& filepath, std::vector<float>& outVertices)
    {
        // Xóa dữ liệu cũ nhưng giữ nguyên vùng nhớ đã cấp phát (capacity)
        outVertices.clear();

        std::ifstream file(filepath);
        if (!file.is_open())
        {
            std::cerr << "[Error] Khong the mo file .ver: " << filepath << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string token;

            while (std::getline(ss, token, ','))
            {
                try
                {
                    outVertices.push_back(std::stof(token));
                }
                catch (const std::invalid_argument&)
                {
                    continue;
                }
            }
        }

        file.close();
    }

    // ============================================================================
    // 2. Đọc file .ind (Indices) truyền bằng tham chiếu &
    // ============================================================================
    inline void LoadIndexBuffer(const std::string& filepath, std::vector<unsigned int>& outIndices)
    {
        // Xóa dữ liệu cũ nhưng giữ nguyên vùng nhớ đã cấp phát (capacity)
        outIndices.clear();

        std::ifstream file(filepath);
        if (!file.is_open())
        {
            std::cerr << "[Error] Khong the mo file .ind: " << filepath << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string token;

            while (std::getline(ss, token, ','))
            {
                try
                {
                    outIndices.push_back(static_cast<unsigned>(std::stoul(token)));
                }
                catch (const std::invalid_argument&)
                {
                    continue;
                }
            }
        }

        file.close();
    }
}