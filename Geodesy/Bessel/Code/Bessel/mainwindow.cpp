#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QDoubleValidator>

long double e_2 = 0.006694384999588; //定义全局变量e2

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 通过设置数据范围和正则表达式来确保用户输入的内容合规
    QIntValidator* validator1 = new QIntValidator(-90, 90, this);
    ui->B1_input_D->setValidator(validator1);
    ui->fs_B1_input_D->setValidator(validator1);
    ui->fs_B2_input_D->setValidator(validator1);
    // 正则表达式说明：
    // ^[-+]?            : 允许以正负号开头
    // (90              : 精确匹配90
    // |[1-8]?\d)$       : 允许0 - 89的整数部分
    QRegularExpression regExp1("^[-+]?(90|[1-8]?\\d)$");
    QRegularExpressionValidator* regexValidator1 = new QRegularExpressionValidator(regExp1, this);
    ui->B1_input_D->setValidator(regexValidator1);
    ui->fs_B1_input_D->setValidator(regexValidator1);
    ui->fs_B2_input_D->setValidator(regexValidator1);

    QIntValidator* validator2 = new QIntValidator(-180, 180, this);
    ui->L1_input_D->setValidator(validator2);
    ui->fs_L1_input_D->setValidator(validator2);
    ui->fs_L2_input_D->setValidator(validator2);
    // 正则表达式说明：
    // ^[-+]?            : 允许以正负号开头
    // (180             : 精确匹配180
    // |1[0-7]\d         : 允许100 - 179的整数部分
    // |[1-9]?\d)$       : 允许0 - 99的整数部分
    QRegularExpression regExp2("^[-+]?(180|1[0-7]\\d|[1-9]?\\d)$");
    QRegularExpressionValidator* regexValidator2 = new QRegularExpressionValidator(regExp2, this);
    ui->L1_input_D->setValidator(regexValidator2);
    ui->fs_L1_input_D->setValidator(regexValidator2);
    ui->fs_L2_input_D->setValidator(regexValidator2);

    // 新建验证器和正则表达式，控制数据在 0 到 59 之间，不允许负号和小数
    QIntValidator* validator3 = new QIntValidator(0, 59, this);
    ui->B1_input_F->setValidator(validator3);
    ui->fs_B1_input_F->setValidator(validator3);
    ui->L1_input_F->setValidator(validator3);
    ui->fs_L1_input_F->setValidator(validator3);
    ui->fs_B2_input_F->setValidator(validator3);
    ui->fs_L2_input_F->setValidator(validator3);
    // 正则表达式说明：
    // ^                : 字符串开始
    // [0-5]?\d         : 匹配 0 到 59 的整数
    // $                : 字符串结束
    QRegularExpression regExp3("^[0-5]?\\d$");
    QRegularExpressionValidator* regexValidator3 = new QRegularExpressionValidator(regExp3, this);
    ui->B1_input_F->setValidator(regexValidator3);
    ui->fs_B1_input_F->setValidator(regexValidator3);
    ui->L1_input_F->setValidator(regexValidator3);
    ui->fs_L1_input_F->setValidator(regexValidator3);
    ui->fs_B2_input_F->setValidator(regexValidator3);
    ui->fs_L2_input_F->setValidator(regexValidator3);

    // 通过设置数据范围和正则表达式来确保用户输入的内容合规
    QDoubleValidator* validator4 = new QDoubleValidator(0.0, 59.9999, 4, this);
    validator4->setNotation(QDoubleValidator::StandardNotation);
    ui->B1_input_M->setValidator(validator4);
    ui->fs_B1_input_M->setValidator(validator4);
    ui->L1_input_M->setValidator(validator4);
    ui->fs_L1_input_M->setValidator(validator4);
    ui->fs_B2_input_M->setValidator(validator4);
    ui->fs_L2_input_M->setValidator(validator4);
    ui->A1_input_M->setValidator(validator4);
    // 正则表达式说明：
    // ^                : 字符串开始
    // ([0-5]?\d)       : 允许 0 - 59 的整数部分
    // (\.\d{1,4})?     : 允许最多 4 位小数
    // $                : 字符串结束
    QRegularExpression regExp4("^([0-5]?\\d)(\\.\\d{1,4})?$");
    QRegularExpressionValidator* regexValidator4 = new QRegularExpressionValidator(regExp4, this);
    ui->B1_input_M->setValidator(regexValidator4);
    ui->fs_B1_input_M->setValidator(regexValidator4);
    ui->L1_input_M->setValidator(regexValidator4);
    ui->fs_L1_input_M->setValidator(regexValidator4);
    ui->fs_B2_input_M->setValidator(regexValidator4);
    ui->fs_L2_input_M->setValidator(regexValidator4);
    ui->A1_input_M->setValidator(regexValidator4);

    // 新建验证器和正则表达式，仅允许非负整数和小数，小数点后最多 6 位
    QDoubleValidator* validator5 = new QDoubleValidator(0.0, std::numeric_limits<double>::max(), 6, this);
    validator5->setNotation(QDoubleValidator::StandardNotation);
    ui->S_input->setValidator(validator5);
    // 正则表达式说明：
    // ^                : 字符串开始
    // \d+              : 匹配至少一个数字（整数部分）
    // (\.\d{1,6})?     : 可选的小数部分，小数点后最多 6 位
    // $                : 字符串结束
    QRegularExpression regExp5("^\\d+(\\.\\d{1,6})?$");
    QRegularExpressionValidator* regexValidator5 = new QRegularExpressionValidator(regExp5, this);
    ui->S_input->setValidator(regexValidator5);

    // 新建验证器和正则表达式，将数据控制在 0 到 360 之间，不允许小数
    QIntValidator* validator6 = new QIntValidator(0, 360, this);
    ui->A1_input_D->setValidator(validator6);
    // 正则表达式说明：
    // ^                : 字符串开始
    // (360             : 精确匹配 360
    // |[1-3]?[0-5]?\d   : 允许 1 到 359 的整数部分
    // |0                : 匹配 0
    // )$                : 字符串结束
    QRegularExpression regExp6("^(360|[1-3]?[0-5]?\\d|0)$");
    QRegularExpressionValidator* regexValidator6 = new QRegularExpressionValidator(regExp6, this);
    ui->A1_input_D->setValidator(regexValidator6);

    //ui->S_input->setReadOnly(true);
    ui->fs_A1_dfm_result->setReadOnly(true);
    ui->fs_A2_dfm_result->setReadOnly(true);
    ui->fs_S_result->setReadOnly(true);
    ui->B2_dfm_result->setReadOnly(true);
    ui->L2_dfm_result->setReadOnly(true);
    ui->A2_dfm_result->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//角度转弧度函数
long double d2r(long double input)
{
    long double radians = input * M_PI / 180.0;
    return radians;
}

//弧度转角度函数
long double r2d(long double input)
{
    long double degree = input * 180.0 / M_PI;
    return degree;
}

void MainWindow::on_zs_pushButton_clicked()
{
    //获取大地线起点纬度B1并转化为小数格式
    long double zs_B1_D = ui->B1_input_D->text().toDouble(); //度
    long double zs_B1_F = ui->B1_input_F->text().toDouble(); //分
    long double zs_B1_M = ui->B1_input_M->text().toDouble(); //秒
    //转化为小数格式
    long double zs_B1 = (zs_B1_D * 3600 + zs_B1_F * 60 + zs_B1_M) / 3600;
    //考虑负数情况
    if(zs_B1_D < 0)
    {
        zs_B1 = - zs_B1;
    }

    //获取大地线起点经度L1并转化为小数格式
    long double zs_L1_D = ui->L1_input_D->text().toDouble(); //度
    long double zs_L1_F = ui->L1_input_F->text().toDouble(); //分
    long double zs_L1_M = ui->L1_input_M->text().toDouble(); //秒
    //转化为小数格式
    long double zs_L1 = (zs_L1_D * 3600 + zs_L1_F * 60 + zs_L1_M) / 3600;
    if(zs_L1_D < 0)
    {
        zs_L1 = - zs_B1;
    }

    //获取大地方位角A1并转化为小数格式
    long double zs_A1_D = ui->A1_input_D->text().toDouble(); //度
    long double zs_A1_F = ui->A1_input_F->text().toDouble(); //分
    long double zs_A1_M = ui->A1_input_M->text().toDouble(); //秒
    //转化为小数格式
    long double zs_A1 = (zs_A1_D * 3600 + zs_A1_F * 60 + zs_A1_M) / 3600;

    //获取大地线长度并转化为小数形式
    long double zs_S = ui->S_input->text().toDouble();

    //由于C++中三角函数的输入为弧度而非角度，因此需要角度转化为弧度
    long double zs_B1_r = d2r(zs_B1);
    long double zs_L1_r = d2r(zs_L1);
    long double zs_A1_r = d2r(zs_A1);

    //计算sin和cosB1，sin和cosA1
    long double sinB1 = sin(zs_B1_r);
    long double cosB1 = cos(zs_B1_r);
    long double sinA1 = sin(zs_A1_r);
    long double cosA1 = cos(zs_A1_r);

    //计算起点的归化纬度
    long double W1 = sqrt(1 - e_2 * pow(sinB1,2)); //W1
    long double sinu1 = (sinB1 * sqrt(1-e_2)) / W1; //sinu1
    long double cosu1 = cosB1 / W1; //cosu1

    //计算辅助函数的值
    long double sinA0 = cosu1 * sinA1; //sinA0
    double sA0 = sinA0;
    long double cotσ1 = (cosu1 * cosA1) / sinu1; //cotσ1
    long double sin2σ1 = (2 * cotσ1) / (pow(cotσ1,2) + 1); //sin2σ1
    long double cos2σ1 = (pow(cotσ1,2) - 1) / (pow(cotσ1,2) +1); //cos2σ1

    //计算系数A,B,C及α,β的值
    //先计算cos²A0以简化表达式形式
    long double cosA0_2 = 1 - pow(sinA0,2);
    //采用克拉索夫斯基椭球元素值
    long double A = 6356863.020 + (10708.949 - 13.474 * cosA0_2) * cosA0_2; //A
    long double B = (5354.469 - 8.978 * cosA0_2) * cosA0_2; //B
    long double C = (2.238 * cosA0_2) * cosA0_2 + 0.006; //C
    long double α = (33523299 - (28189 - 70 * cosA0_2) * cosA0_2) * pow(10,-10) * 206265; //α
    long double β = (0.2907 - 0.0010 * cosA0_2) * cosA0_2; //β

    //计算球面长度
    long double S = zs_S; //统一变量名格式，提高可读性
    long double σ0 = (S - (B + C * cos2σ1) * sin2σ1) / A; //σ0
    //先计算sin2σ0,cos2σ0以简化表达式
    long double sin2σ0 = sin(2*σ0);
    long double cos2σ0 = cos(2*σ0);
    //
    long double sin2σ01 = sin2σ1 * cos2σ0 + cos2σ1 * sin2σ0; //sin2(σ0+σ1)
    long double cos2σ01 = cos2σ1 * cos2σ0 - sin2σ1 * sin2σ0; //cos2(σ0+σ1)
    long double σ = σ0 + (B + 5 * C * cos2σ01) * sin2σ01 / A; //σ

    //计算经差改正数
    //先计算sin2σ,cos2σ,sin2(σ1+σ)以简化表达式
    long double sin2σ = sin(2*σ);
    long double cos2σ = cos(2*σ);
    long double sin2σ1σ = sin2σ1 * cos2σ + cos2σ1 * sin2σ;
    //
    long double δ = (α * σ + β * sin2σ1σ - sin2σ1) * sinA0;

    //计算终点大地坐标及大地方位角
    //先计算sinσ，cosσ以简化表达式
    long double sinσ = sin(σ);
    long double cosσ = cos(σ);
    //
    long double sinu2 = sinu1 * cosσ + cosu1 * cosA1 * sinσ;
    long double zs_B2_r = atan(sinu2 / (sqrt(1-e_2) * sqrt(1-pow(sinu2,2)))); //B2（弧度）
    long double λ = atan(sinA1 * sinσ / (cosu1 * cosσ - sinu1 * sinσ * cosA1)); //λ(弧度）
    //判断λ的符号
    if(sinA1 > 0 && tan(λ) > 0)
    {
        λ = abs(λ);
    }
    else if(sinA1 > 0 && tan(λ) < 0)
    {
        λ = M_PI - abs(λ);
    }
    else if(sinA1 < 0 && tan(λ) < 0)
    {
        λ = -abs(λ);
    }
    else if(sinA1 < 0 && tan(λ) > 0)
    {
        λ = abs(λ) - M_PI;
    }
    //
    long double zs_L2_r = zs_L1_r + λ - δ / 206265; //L2（弧度）
    long double zs_A2_r = atan(cosu1 * sinA1 / (cosu1 * cosσ * cosA1 - sinu1 * sinσ)); //A2（弧度）
    //判断A2的最终大小
    if(sinA1 < 0 && tan(zs_A2_r) > 0)
    {
        zs_A2_r = abs(zs_A2_r);
    }
    else if(sinA1 < 0 && tan(zs_A2_r) < 0)
    {
        zs_A2_r = M_PI - abs(zs_A2_r);
    }
    else if(sinA1 > 0 && tan(zs_A2_r) > 0)
    {
        zs_A2_r = M_PI + abs(zs_A2_r);
    }
    else if(sinA1 > 0 && tan(zs_A2_r) < 0)
    {
        zs_A2_r = 2 * M_PI - abs(zs_A2_r);
    }

    //B2弧度转角度
    long double zs_B2_d = r2d(zs_B2_r);
    //B2度转度分秒
    int zs_B2_D = zs_B2_d;
    int zs_B2_F = abs((zs_B2_d - zs_B2_D)) * 60;
    double zs_B2_M = (abs((zs_B2_d - zs_B2_D)) * 60 - zs_B2_F) * 60;
    //显示B2结果
    QString B2 = QString::number(zs_B2_D) + "°" + QString::number(zs_B2_F) + "'" +QString::number(zs_B2_M) + "''";
    ui->B2_dfm_result->setText(B2);

    //L2弧度转角度
    long double zs_L2_d = r2d(zs_L2_r);
    //L2度转度分秒
    int zs_L2_D = zs_L2_d;
    int zs_L2_F = abs((zs_L2_d - zs_L2_D)) * 60;
    double zs_L2_M = (abs((zs_L2_d - zs_L2_D)) * 60 - zs_L2_F) * 60;
    //显示L2结果
    QString L2 = QString::number(zs_L2_D) + "°" + QString::number(zs_L2_F) + "'" +QString::number(zs_L2_M) + "''";
    ui->L2_dfm_result->setText(L2);

    //A2弧度转角度
    long double zs_A2_d = r2d(zs_A2_r);
    //A2度转度分秒
    int zs_A2_D = zs_A2_d;
    int zs_A2_F = abs((zs_A2_d - zs_A2_D)) * 60;
    double zs_A2_M = (abs((zs_A2_d - zs_A2_D)) * 60 - zs_A2_F) * 60;
    //显示A2结果
    QString A2 = QString::number(zs_A2_D) + "°" + QString::number(zs_A2_F) + "'" +QString::number(zs_A2_M) + "''";
    ui->A2_dfm_result->setText(A2);
}


void MainWindow::on_fs_pushButton_clicked()
{

    //获取大地线起点纬度B1并转化为小数格式
    long double fs_B1_D = ui->fs_B1_input_D->text().toDouble(); //度
    long double fs_B1_F = ui->fs_B1_input_F->text().toDouble(); //分
    long double fs_B1_M = ui->fs_B1_input_M->text().toDouble(); //秒
    //转化为小数格式
    long double fs_B1 = (abs(fs_B1_D) * 3600 + fs_B1_F * 60 + fs_B1_M) / 3600;
    //考虑负数情况
    if(fs_B1_D < 0)
    {
        fs_B1 = - fs_B1;
    }

    //获取大地线起点经度L1并转化为小数格式
    long double fs_L1_D = ui->fs_L1_input_D->text().toDouble(); //度
    long double fs_L1_F = ui->fs_L1_input_F->text().toDouble(); //分
    long double fs_L1_M = ui->fs_L1_input_M->text().toDouble(); //秒
    //转化为小数格式
    long double fs_L1 = (abs(fs_L1_D) * 3600 + fs_L1_F * 60 + fs_L1_M) / 3600;
    //考虑负数情况
    if(fs_L1_D < 0)
    {
        fs_L1 = - fs_L1;
    }

    //获取大地线终点纬度B2并转化为小数格式
    long double fs_B2_D = ui->fs_B2_input_D->text().toDouble(); //度
    long double fs_B2_F = ui->fs_B2_input_F->text().toDouble(); //分
    long double fs_B2_M = ui->fs_B2_input_M->text().toDouble(); //秒
    //转化为小数格式
    long double fs_B2 = (abs(fs_B2_D) * 3600 + fs_B2_F * 60 + fs_B2_M) / 3600;
    //考虑负数情况
    if(fs_B2_D < 0)
    {
        fs_B2 = - fs_B2;
    }
    qDebug() << "B2:" << double(fs_B2);

    //获取大地线终点经度L2并转化为小数格式
    long double fs_L2_D = ui->fs_L2_input_D->text().toDouble(); //度
    long double fs_L2_F = ui->fs_L2_input_F->text().toDouble(); //分
    long double fs_L2_M = ui->fs_L2_input_M->text().toDouble(); //秒
    //转化为小数格式
    long double fs_L2 = (abs(fs_L2_D) * 3600 + fs_L2_F * 60 + fs_L2_M) / 3600;
    //考虑负数情况
    if(fs_L2_D < 0)
    {
        fs_L2 = - fs_L2;
    }

    //由于C++中三角函数的输入为弧度而非角度，因此需要角度转化为弧度
    long double fs_B1_r = d2r(fs_B1);
    long double fs_L1_r = d2r(fs_L1);
    long double fs_B2_r = d2r(fs_B2);
    long double fs_L2_r = d2r(fs_L2);

    //计算sin和cosB1，sin和cosB2
    long double sinB1 = sin(fs_B1_r);
    long double cosB1 = cos(fs_B1_r);
    long double sinB2 = sin(fs_B2_r);
    long double cosB2 = cos(fs_B2_r);

    //辅助计算
    long double W1 = sqrt(1 - e_2 * pow(sinB1,2)); //W1
    long double sinu1 = (sinB1 * sqrt(1-e_2)) / W1; //sinu1
    qDebug() << "sinu1:" << double(sinu1);
    long double cosu1 = cosB1 / W1; //cosu1
    qDebug() << "cosu1:" << double(cosu1);
    long double W2 = sqrt(1 - e_2 * pow(sinB2,2)); //W2
    long double sinu2 = (sinB2 * sqrt(1-e_2)) / W2; //sinu2
    qDebug() << "sinu2:" << double(sinu2);
    long double cosu2 = cosB2 / W2; //cosu2
    qDebug() << "cosu2:" << double(cosu2);
    long double L = fs_L2_r - fs_L1_r; //L
    long double a1 = sinu1 * sinu2; //a1
    qDebug() << "a1:" << double(a1);
    long double a2 = cosu1 * cosu2; //a2
    qDebug() << "a2:" << double(a2);
    long double b1 = cosu1 * sinu2; //b1
    qDebug() << "b1:" << double(b1);
    long double b2 = sinu1 * cosu2; //b2
    qDebug() << "b2:" << double(b2);

    long double δ = 0; //初始δ、
    long double pre_δ;
    long double λ = L + δ; //初始λ
    long double sinλ = 0; //初始sinλ
    long double cosλ = 0; //初始cosλ
    long double p = 0; //初始p
    long double q = 0; //初始q
    long double A1 = 0; //初始A1
    long double sinσ = 0; //初始sinσ
    long double cosσ = 0; //初始cosσ
    long double σ = 0; //初始σ
    long double cosA0_2 = 0; //初始cos²A0
    long double x = 0; //初始x
    int n = 0; //迭代次数
    long double tiny_value = 1e-6; //定义微小量
    do
    {
        //上一次迭代的δ
        pre_δ = δ;

        //先计算sinλ,cosλ以简化表达式
        sinλ = sin(λ);
        cosλ = cos(λ);
        //
        p = cosu2 * sinλ; //当前迭代的p
        q = b1 - b2 * cosλ; //当前迭代的q
        A1 = atan(p/q); //当前迭代的A1
        //判断A1的最终大小
        if(p > 0 && q > 0)
        {
            A1 = abs(A1);
        }
        else if(p > 0 && q < 0)
        {
            A1 = M_PI - abs(A1);
        }
        else if(p < 0 && q < 0)
        {
            A1 = M_PI + abs(A1);
        }
        else if(p < 0 && q > 0)
        {
            A1 = 2 * M_PI - abs(A1);
        }
        //先计算sinA1,cosA1以简化表达式
        long double sinA1 = sin(A1);
        long double cosA1 = cos(A1);
        //
        sinσ = p * sinA1 + q * cosA1; //当前迭代的sinσ
        cosσ = a1 + a2 * cosλ; //当前迭代的cosσ
        σ = atan(sinσ/cosσ); //当前迭代的σ
        //判断σ的最终大小
        if(cosσ > 0)
        {
            σ = abs(σ);
        }
        else if(cosσ < 0)
        {
            σ = M_PI - abs(σ);
        }
        //
        long double sinA0 = cosu1 * sinA1; //当前迭代的sinA0
        cosA0_2 = 1 - pow(sinA0,2); //当前迭代的cos²A0
        x = 2 * a1 - cosA0_2 * cosσ; //当前迭代的x
        //采用克拉索夫斯基椭球元素值计算α，β'
        long double α = (33523299 - (28189 - 70 * cosA0_2) * cosA0_2) * pow(10,-10); //α
        long long β_p = (28189 - 94 * cosA0_2) * pow(10,-10); //β'
        //
        δ = (α * σ - β_p * x * sinσ) * sinA0 * 206265; //当前迭代的δ
        λ = L + δ / 206265; //当前迭代的λ
        n++;

        //test debug代码
        /*
        if(n == 1 or n == 2 or n == 3 or n == 4)
        {
            qDebug() << "当前n:" << n;
            qDebug() << "sinλ:" << double(sinλ);
            qDebug() << "cosλ:" << double(cosλ);
            qDebug() << "p:" << double(p);
            qDebug() << "q:" << double(q);
            qDebug() << "A1:" << double(A1);
            qDebug() << "sinA1:" << double(sinA1);
            qDebug() << "cosA1:" << double(cosA1);
            qDebug() << "sinσ:" << double(sinσ);
            qDebug() << "cosσ:" << double(cosσ);
            qDebug() << "σ:" << double(σ);
            qDebug() << "sinA0:" << double(sinA0);
            qDebug() << "x:" << double(x);
            qDebug() << "α:" << double(α);
            qDebug() << "δ:" << double(δ);
            qDebug() << "β':" << double(β_p);
            qDebug() << "=========================";
        }*/

    }while(abs(δ - pre_δ) > tiny_value);
    //qDebug() << "迭代次数:" << n;

    //计算A,B'',C''
    long double A = 6356863.020 + (10708.949 - 13.474 * cosA0_2) * cosA0_2;
    long double B_pp = 10708.938 - 17.956 * cosA0_2;
    long double C_pp = 4.487;
    //test debug代码
    /*
    qDebug() << "A:" << double(A);
    qDebug() << "B'':" << double(B_pp);
    qDebug() << "C'':" << double(C_pp);
    */

    //计算大地线长度S
    long double y = (pow(cosA0_2,2) - 2 * pow(x,2)) * cosσ;
    long double S = A * σ + (B_pp * x + C_pp * y) * sinσ; //S

    //计算反方位角A2
    long double A2 = atan((cosu1 * sinλ) / (b1 * cosλ - b2)); //A2
    //判断A2的最终大小
    if(p > 0 && q > 0)
    {
        A2 = abs(A2) + M_PI;
    }
    else if(p > 0 && q < 0)
    {
        A2 = 2 * M_PI - abs(A2);
    }
    else if(p < 0 && q < 0)
    {
        A2 = abs(A2);
    }
    else if(p < 0 && q > 0)
    {
        A2 = M_PI - abs(A2);
    }

    //A1弧度转角度
    long double fs_A1_d = r2d(A1);
    //A1度转度分秒
    int fs_A1_D = fs_A1_d;
    int fs_A1_F = abs((fs_A1_d - fs_A1_D)) * 60;
    double fs_A1_M = (abs((fs_A1_d - fs_A1_D)) * 60 - fs_A1_F) * 60;
    //显示A1结果
    QString A1_str = QString::number(fs_A1_D) + "°" + QString::number(fs_A1_F) + "'" +QString::number(fs_A1_M) + "''";
    ui->fs_A1_dfm_result->setText(A1_str);
    ui->fs_A1_dfm_result->setReadOnly(true);

    //A2弧度转角度
    long double fs_A2_d = r2d(A2);
    //A2度转度分秒
    int fs_A2_D = fs_A2_d;
    int fs_A2_F = abs((fs_A2_d - fs_A2_D)) * 60;
    double fs_A2_M = (abs((fs_A2_d - fs_A2_D)) * 60 - fs_A2_F) * 60;
    //显示A2结果
    QString A2_str = QString::number(fs_A2_D) + "°" + QString::number(fs_A2_F) + "'" +QString::number(fs_A2_M) + "''";
    ui->fs_A2_dfm_result->setText(A2_str);
    ui->fs_A2_dfm_result->setReadOnly(true);

    //显示S结果
    QString S_str = QString::number(double(S),'f',6) + "m";
    ui->fs_S_result->setText(S_str);
    ui->fs_S_result->setReadOnly(true);
}

