# CS205 Project 1 Report
**Name:** 龚凌琥 (GONG Linghu)  
**SID:** 12110631

## Part 1 - Analysis

### 输入输出处理
项目的问题是计算多种不同形式输入的两个数的乘积。项目需要判断输入是否合法，因此，首先需要定义一个合法的数的输入。

定义一个合法的数的输入为：`[符号位(+-)]整数部分[.小数部分][e(E)[符号位(+-)]指数部分(整数)]`。

在编写代码时，将指针后移，根据非数位字符确定是否合法即可。

同时，为了计算方便（同时保证计算精度），把浮点数部分全部转换为整数，例：`1.001e100` -> `1001e97`。输出时根据指数部分计算小数点位置即可。在输出较小时，采用小数形式输出，指数部分较大时，采用科学计数法输出。

### 乘法计算
计算乘法部分，采用了快速傅里叶变换将多项式系数表示转为点值表示，这样可以以 $O(n\log n)$ 的时间复杂度计算有效位数较多的乘法。

对于一个 $n$ 位十进制整数，可以用一个多项式 $A(x)$ 表示
$$
A(x)=\sum_{i=0}^{n-1}a_ix^i
$$
其中 $x=10$。

然后使用 Cooley-Tukey 算法将该多项式转换为点值表示。该算法基于一种分治思想，可以将离散傅里叶变换和逆离散傅里叶变换的时间复杂度优化到 $O(n\log n)$。

我们对多项式 $A(x)$ 进行考虑。首先我们把 $A(x)$ 的系数按照下标奇偶性分类
$$
\begin{align}
A(\omega^k_{n})
&= \sum^{\frac{n}{2} – 1}_{i=0}a_{2i}(\omega^{k}_{n})^{2i} + \sum^{\frac{n}{2}-1}_{i=0}a_{2i+1}({\omega^{k}_n})^{2i + 1} \\
& = \sum^{\frac{n}{2} – 1}_{i=0}a_{2i}(\omega^{k}_{n})^{2i} + \omega_n^k\sum^{\frac{n}{2}-1}_{i=0}a_{2i+1}({\omega^{k}_n})^{2i} \\
& = \sum^{\frac{n}{2} – 1}_{i=0}a_{2i}(\omega^{ki}_{n})^{2} + \omega_n^k\sum^{\frac{n}{2}-1}_{i=0}a_{2i+1}({\omega^{ki}_n})^{2}
\end{align}
$$

当 $k < \frac{n}{2}$ 时，有
$$
A_1(\omega^k_n) = \sum_{i=0}^{\frac{n}{2}-1}a_{2i}{\omega_{\frac{n}{2}}^{ki}} + \omega^k_n\sum_{i=0}^{\frac{n}{2}-1}a_{2i+1}\omega^{ki}_{\frac{n}{2}}
$$
当 $k \ge \frac{n}{2}$ 时（在此时，用 $k + \frac{n}{2}$ 代表 $k$ ），有
$$
A_2(\omega_n^k) = \sum^{n-1}_{i=0}a_{2i}\omega^{ki}_{\frac{n}{2}} + \omega^{k + \frac{n}{2}}_n\sum_{i=0}^{\frac{n}{2}-1}a_{2i+1}\omega^{ki}_{\frac{n}{2}}
$$
对于 $\omega^{k + \frac{n}{2}}_n$，有
$$
\omega^{k + \frac{n}{2}}_n = e^{\frac{2 \pi k \mathbf{i}}{n}} \times e^{\frac{2 \pi \times \frac{n}{2} \mathbf{i}}{n}} = e^{\frac{2 \pi k \mathbf{i}}{n}} \times e^{\pi \mathbf{i}}
$$

根据欧拉恒等式 $e^{\pi \mathbf{i}} = -1$，可知
$$
\omega^{k+\frac{n}{2}}_n = -\omega_{n}^{k}
$$
因此
$$
A_2(\omega_n^k) = \sum^{n-1}_{i=0}a_{2i}\omega^{ki}_{\frac{n}{2}} – \omega^{k}_n\sum_{i=0}^{\frac{n}{2}-1}a_{2i+1}\omega^{ki}_{\frac{n}{2}}
$$
这样就可以将带入的 $\omega$ 折半，然后递归分治即可。

```C++
// n 是多项式长度扩大到 2^k 长度后的长度
// a 表示传入的多项式的系数, inv 表示代入的单位根是否是倒数
void fft(int n, Complex *a, bool inv) {
    if (n == 1) return;
    static Complex buf[MAXN];
    int m = n >> 1;
    // 按照奇偶分类
    for (int i = 0; i < m; i++) {
        buf[i] = a[2 * i];
        buf[i + m] = a[2 * i + 1];
    }
    // 递归运算
    for (int i = 0; i < n; i++)
        a[i] = buf[i];
    fft(m, a, inv);
    fft(m, a + m, inv);
    // 计算 DFT(A(x))
    Complex w = Complex(1.0, 0.0), 
            wn = Complex(cos(2 * PI / n), sin(2 * PI / n));
    if (inv) wn = getConj(wn);
    for (int i = 0; i < m; i++) {
        buf[i] = a[i] + w * a[i + m];
        buf[i + m] = a[i] - w * a[i + m];
        w = w * wn;
    }
    for (int i = 0; i < n; i++)
        a[i] = buf[i];
}
```

递归实现的FFT运行速度较慢，我们考虑一下采用迭代方式实现。先考虑一下递归树。对于一个 $n=8$ 时递归树最后一层，把每个数原始下标的二进制表示和在最底层数组的下标的二进制列出来：

- $a_0(000) \;\;000 $
- $a_4(100) \;\; 001$
- $a_2(010) \;\; 010$ 
- $a_6(110) \;\; 011$
- $a_1(001) \;\; 100$
- $a_5(101) \;\; 101$
- $a_3(011) \;\; 110$
- $a_7(111) \;\; 111$

可以发现，原始下标是底层下标的二进制位的反转。设 $rev(x)$ 为 $x$ 在二进制位上的反转，则 $a[x] = a'[rev[x]]$。这样我们就找到了最低层下标的对应规律，可以考虑迭代进行 FFT 了。用蝴蝶操作将重复的表达式 $\omega \times a[i+m]$ 提取出来，就可以不使用 `buf` 数组，在 `a` 中直接计算进行，具体的代码如下

```C++
for (int i = 0; i < m; i++) {
    R Complex t = w * a[i + m];
    a[i + m] = a[i] - t;
    a[i] = a[i] + t;
    w = w * wn;
}
```

接着，只需要自底向上对 FFT 的过程进行追踪，即可写出迭代的 FFT，具体代码见第二部分。

## Part2 - Code

**包含关键部分代码。**
```cpp
// source.cpp
// ...

void fft(Complex *a, bool inv) {
    lim = 0;
    while ((1 << lim) < n)
        lim++;
    
    // 蝴蝶变换，自底向上处理
    for (register int i = 0; i < n; i++) {
        register int t = 0;
        for (register int j = 0; j < lim; j++)
            if ((i >> j) & 1)
                t |= (1 << (lim - j - 1));
        if (i < t)
            swap(a[i], a[t]);
    }
    
    // 迭代处理
    for (register int l = 2; l <= n; l <<= 1) {
        int m = l >> 1;
        Complex wn(cos(2 * PI / l), sin(2 * PI / l));
        if (inv)
            wn = wn.getConj();
        for (register Complex *p = a; p != a + n; p += l) {
            register Complex w(1.0, 0.0);
            for (register int i = 0; i < m; i++) {
                register Complex t = w * p[i + m];
                p[i + m] = p[i] - t;
                p[i] = p[i] + t;
                w = w * wn;
            }
        }
    } 
}

void multiply() {
    while (n < a_len + b_len)
        n <<= 1;
    
    fft(a, 0);
    fft(b, 0);
    
    for (register int i = 0; i < n; i++)
        a[i] = a[i] * b[i];
        
    fft(a, 1);
    
    for (register int i = 0; i < n; i++)
        a[i].real = a[i].real / (double)n;
    
    // 将大于9的多项式系数前移
    for (register int i = 0; i < n; i++) {
        if(!(a[i].real <= 9)) {
            a[i + 1].real += (int)(a[i].real + 0.5) / 10;
            a[i].real = a[i].real - ((int)(a[i].real + 0.5) / 10) * 10;   
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Invalid input length!" << endl;
        return 0;
    }
    else {
        std::vector<int> num;

        a_len = 0, b_len = 0;
        a_exp = 0, b_exp = 0;
        a_point = -1, b_point = -1;

        // A的输入部分，需要在多处检查输入合法性
        char *p = argv[1];
        bool is_exp = false, neg_exp = false;
        while (*p != '\0') {
            if (isdigit(*p)) {
                if (!is_exp) num.push_back(*p - '0');
                else a_exp = a_exp * 10 + (*p - '0');
            }
            else if (*p == '.' && a_point == -1) a_point = num.size();
            else if ((*p == 'e' || *p == 'E') && !is_exp) is_exp = true;
            else if (*p == '-' && (num.size() == 0 || (is_exp && a_exp == 0)))
            {
                if (!is_exp) a_neg = true;
                else neg_exp = true;
            }
            else if (*p == '+' && (num.size() == 0 || (is_exp && a_exp == 0)))
                continue;
            else {
                cout << "The input cannot be interpret as numbers!" << endl;
                return 0;
            }
            ++p;
        }
        if (neg_exp) a_exp *= -1;
        if (is_exp && a_exp == 0) {
            cout << "The input cannot be interpret as numbers!" << endl;
            return 0;
        }

        // 将小数全部转为整数+指数的形势
        if (a_point == -1)
            a_point = num.size();
        a_len = num.size();
        a_exp += a_point - a_len;

        // 倒序存储，便于FFT计算
        int flag = 0;
        while (num[flag] == 0) ++flag;
        for (register int i = flag; i < a_len; i++)
            a[a_len - i - 1].real = (double)num[i];

        // B的输入部分，同上
        p = argv[2];
        is_exp = false, neg_exp = false;
        num.clear();
        while (*p != '\0') {
            if (isdigit(*p)) {
                if (!is_exp) num.push_back(*p - '0');
                else b_exp = b_exp * 10 + (*p - '0');
            }
            else if (*p == '.' && b_point == -1) b_point = num.size();
            else if ((*p == 'e' || *p == 'E') && !is_exp) is_exp = true;
            else if (*p == '-' && (num.size() == 0 || (is_exp && b_exp == 0)))
            {
                if (!is_exp) b_neg = true;
                else neg_exp = true;
            }
            else {
                cout << "The input cannot be interpret as numbers!" << endl;
                return 0;
            }
            ++p;
        }
        if (neg_exp) b_exp *= -1;
        if (is_exp && b_exp == 0) {
            cout << "The input cannot be interpret as numbers!" << endl;
            return 0;
        }
        if (b_point == -1)
            b_point = num.size();
        b_len = num.size();
        b_exp += b_point - b_len;

        flag = 0;
        while (num[flag] == 0) ++flag;
        for (register int i = flag; i < b_len; i++)
            b[b_len - i - 1].real = (double)num[i];
    }
	 
    multiply();

    // 删除前缀和后缀0
    int pre_flag = n - 1;
    while (fabs(a[pre_flag].real) <= 0.50000) pre_flag--;
    int suf_flag = 0;
    while (fabs(a[suf_flag].real) <= 0.50000) suf_flag++;

    char *p = argv[1];
    while (*p != '\0') cout << *p++;
    cout << " * ";
    p = argv[2];
    while (*p != '\0') cout << *p++;
    cout << " = ";

    if (a_neg ^ b_neg) cout << '-';

    // 判断有效位数，如果过多采用科学计数法
    int exp_sum = a_exp + b_exp + suf_flag;
    if (abs(exp_sum) > 20 || (pre_flag - suf_flag) > 20) {
        for (register int i = pre_flag; i >= suf_flag; i--) {
            cout << (int)(a[i].real + 0.5);
            if (i == pre_flag && i != suf_flag)
                cout << ".";
        }
        if (exp_sum != 0)
            cout << 'e' << exp_sum;
    }
    else {
        if (exp_sum < 0 && exp_sum + (pre_flag - suf_flag + 1) < 0) {
            cout << "0.";
            for (register int i = 1; i <=  -exp_sum  - (pre_flag - suf_flag + 1); i++)
                cout << 0;
        }
        for (register int i = pre_flag; i >= suf_flag; i--) {
            cout << (int)(a[i].real + 0.5);
            if (-i == a_exp + b_exp && i != suf_flag)
                cout << ".";
        }
        if (a_exp + b_exp > 0)
            for (register int i = 1; i <= a_exp + b_exp; i++)
                cout << 0;
    }
    cout << endl;
    
    return 0;
}
```

## Part 3 - Result & Verification

### Test Case 1
```bash
[ice@MiWiFi-RA81-srv Project1]$ ./mul 2 3
2 * 3 = 6
[ice@MiWiFi-RA81-srv Project1]$ ./mul 3.1416 2
3.1416 * 2 = 6.2832
[ice@MiWiFi-RA81-srv Project1]$ ./mul 3.1415 2.0e-2
3.1415 * 2.0e-2 = 0.06283
[ice@MiWiFi-RA81-srv Project1]$ ./mul a  2
The input cannot be interpret as numbers!
[ice@MiWiFi-RA81-srv Project1]$ ./mul 1234567890
Invalid input length!
[ice@MiWiFi-RA81-srv Project1]$ ./mul 1234567890 1234567890
1234567890 * 1234567890 = 15241578750190521
[ice@MiWiFi-RA81-srv Project1]$ ./mul 1.0e200 1.0e200
1.0e200 * 1.0e200 = 1e400
[ice@MiWiFi-RA81-srv Project1]$ 
```

### Test Case 2
```bash
[ice@MiWiFi-RA81-srv Project1]$ ./mul 1e-2 222e222
1e-2 * 222e222 = 2.22e220
[ice@MiWiFi-RA81-srv Project1]$ ./mul -2123 2e1
-2123 * 2e1 = -42460
[ice@MiWiFi-RA81-srv Project1]$ ./mul 0213eeee1 -1e1
The input cannot be interpret as numbers!
[ice@MiWiFi-RA81-srv Project1]$ ./mul 821.33 --2123e1
The input cannot be interpret as numbers!
[ice@MiWiFi-RA81-srv Project1]$ ./mul 21783.3e--2 3.3
21783.3e--2 * 3.3 = 718.8489
[ice@MiWiFi-RA81-srv Project1]$ ./mul 821.33 --2123e1
The input cannot be interpret as numbers!
[ice@MiWiFi-RA81-srv Project1]$ ./mul 1-1e2 -11-1e3
The input cannot be interpret as numbers!
```

## Part 4 - Difficulties & Solutions

### 处理小数
开始时考虑使用浮点数对小数部分进行处理，后来发现有效数字位数一多，会有精度损失。考虑将一个数表示为 `[整数部分]E[指数部分]`，再进行计算，即可保证计算精度。以小数形式输出时只需要结合前导0和后缀0的信息计算小数点位置和前导0的数量即可。

### 输入处理
主要的困难在于处理相对原始的字符串输入，需要判断各种可能出现的情况。如果能够使用正则表达式匹配有效输入 ``[符号位(+-)]整数部分[.小数部分][e(E)[符号位(+-)]指数部分(整数)]`` ，程序将会比较容易编写。