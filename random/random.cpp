#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

// 自定义-随机数生成器
class XorShift32 {
public:
    using result_type = uint32_t;
    explicit XorShift32(std::size_t seed) : state(uint32_t(seed)) {}

    constexpr uint32_t operator()() {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        return state;
    }
    static constexpr uint32_t min() {
        return 0;
    }
    static constexpr uint32_t max() {
        return UINT32_MAX;
    }

private:
    uint32_t state;
};

class Random {
public:
    Random(int a, int b) : rng_(std::random_device{}()), uni_(a, b) {}
    int operator()() {
        return uni_(rng_);
    }

private:
    std::mt19937 rng_;
    std::uniform_int_distribution<int> uni_; 
};

void test1() 
{
    std::vector<int> arr(10);
    // 1.time(nullptr) 生成的种子精度低
    // 2.std::chrono::high_resolution_clock::now().time_since_epoch().count();
    // 3.从操作系统读出一个接近真随机的种子
    std::mt19937 rng(std::random_device{}()); 

    // 均匀分布
    std::uniform_int_distribution<int> uni(0,100);
    auto gen = std::bind(uni, std::ref(rng));

    int n = 10;
    while (n--) {
        std::generate(arr.begin(), arr.end(), std::ref(gen));
        for (auto& x : arr)
            std::cout << x << " ";
        std::cout << "\n";
    }
}

// Use Custom RNG
void test2() 
{
    XorShift32 rng(std::random_device{}());
    std::uniform_real_distribution<float> uni(0.0f, 1.0f);
    std::cout << uni(rng) << "\n";
    std::cout << uni(rng) << "\n";
    std::cout << uni(rng) << "\n";
    std::cout << uni(rng) << "\n";
    std::cout << uni(rng) << "\n";
    std::cout << uni(rng) << "\n";

}

void test_case1()
{
    std::vector<std::string> choice{"Red", "White", "Black", "Pink"};
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> uni(0, choice.size()-1);

    std::cout << "-- " << choice[uni(rng)] << "\n";
    std::cout << "-- " << choice[uni(rng)] << "\n";
    std::cout << "-- " << choice[uni(rng)] << "\n";
    std::cout << "-- " << choice[uni(rng)] << "\n";
    std::cout << "-- " << choice[uni(rng)] << "\n";
}

void test_case2()
{
    // -- random generate
    Random rng(0,100);
    std::vector<int> arr;
    std::generate_n(std::back_insert_iterator(arr), 10, std::ref(rng));
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>{std::cout, " "}); std::cout << "\n";

    // -- random shuffle
    arr.resize(40);
    std::iota(arr.begin(), arr.end(), 1);
    std::shuffle(arr.begin(), arr.end(), XorShift32{1});
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>{std::cout, " "}); std::cout << "\n";
}

void test_case3()
{
    using namespace std;
    vector<std::string> rank{"A", "B", "C", "D", "E"};
    vector<float> probability{0.5f, 0.3f, 0.1f, 0.05f, 0.05f};
    vector<float> scanned; scanned.reserve(10);
    // -- 前缀和
    inclusive_scan(probability.begin(), probability.end(), back_inserter(scanned));
    cout << "scanned: "; copy(scanned.begin(), scanned.end(), ostream_iterator<float>{cout, " "});

    mt19937 rng(random_device{}());
    auto gen = [&]() -> string {
        uniform_real_distribution<float> uni(0.0f, 1.0f);
        float ret = uni(rng);
        cout << ret << " - "; 
        // O(logN)
        auto it = lower_bound(scanned.begin(), scanned.end(), ret);
        std::size_t index = distance(scanned.begin(), it);
        return rank[index];
    };
    cout << "\n";
    cout << gen() << "\n";
    cout << gen() << "\n";
    cout << gen() << "\n";
    cout << gen() << "\n";
    cout << gen() << "\n";
}

int main(int argc, char* argv[])
{
    // test1();
    // test2();
    // test_case1();
    // test_case2();
    test_case3();

}