#include <iostream>
#include <vector>
#include <memory>
#include <string>

// =====================================
// 現実世界の例：支払い方法
// =====================================

// ---- 基底クラス----
class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;

    //派生クラスごとに処理が変わる
    virtual void Pay(int yen) const = 0;

    virtual std::string Name() const = 0;
};

// ----派生クラス１現金----
class Cash : public PaymentMethod {
public:
    void Pay(int yen) const override {
        std::cout << "現金で" << yen << "円 を支払いましたお釣りが出るかも\n";
    }
    std::string Name() const override { return "現金"; }
};

// ---- 派生クラス2クレジットカード ----
class CreditCard : public PaymentMethod {
public:
    CreditCard(std::string brand) : brand_(std::move(brand)) {}

    void Pay(int yen) const override {
        std::cout << brand_ << "カードで " << yen << "円を支払いました\n";
    }
    std::string Name() const override { return "クレジットカード(" + brand_ + ")"; }

private:
    std::string brand_;
};

// ---- 派生クラス３QR決済 ----
class QRPay : public PaymentMethod {
public:
    QRPay(std::string service) : service_(std::move(service)) {}

    void Pay(int yen) const override {
        std::cout << service_ << "で " << yen << "円 を支払いました\n";
    }
    std::string Name() const override { return "QR決済(" + service_ + ")"; }

private:
    std::string service_;
};

int main() {
    // =====================================
    // インスタンス生成
    // =====================================
    std::vector<std::unique_ptr<PaymentMethod>> methods;
    methods.push_back(std::make_unique<Cash>());
    methods.push_back(std::make_unique<CreditCard>("VISA"));
    methods.push_back(std::make_unique<QRPay>("PayPay"));

    // =====================================
    // 実例を示す：同じ型(PaymentMethod*)としてまとめて扱えるのに、
    // 実際に呼ばれる Pay()は種類ごとに変わる
    // =====================================
    int price = 1200;
    std::cout << "商品価格: " << price << "円\n\n";

    for (const auto& m : methods) {
        std::cout << "[" << m->Name() << "] ";
        m->Pay(price);
    }

    return 0;
}
