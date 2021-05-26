# Mysql

## 启动/停止 服务

* 启动：以管理员身份启动命令提示符：net start mysql80(80:本机上的服务名称)
* 停止：同上，命令：net stop mysql80

## 登陆Mysql

* 通过Mysql自带的客户端进入[^自带客户端]
  * exit命令退出或者Ctrl+c
  * 不推荐使用，只能供root用户使用

* 通过管理员命令提示符
  * 命令：mysql -h 主机名[^h] -P[^P]端口号-u[^u] 用户名-p[^1]
  * 若在本机登陆，则 主机名和端口号都可以省略
  * 退出：exit或Ctrl+c

## Mysql命令

### Mysql常见命令

* 查看所有数据库：show databases;

* 进入其中一个数据库： use+数据库名字;

* 查看当前库中的表： show tables;

* 在一个库中查看另外一个库：show tables from+另外一个库名;

  * 此时还在原本那个库

* 创建表：create table+表名(

  ​		列名 列类型，

  ​		列名  列类型，

  ​		.....................(最后一行不用加 , )

  )

* 查看此时的位置：select database();

* 查看表的结构：desc +表的名字;

* 查看表中的数据：select * from +表名;

* 查看当前mysql版本：

  * select version();
  * 退出后 ：mysql --version
  * 退出后:   mysql -V

### Mysql语法规范

1. 不区分大小写，但建议关键字大写，表明、列名小写
2. 每条命令最好用分号结尾
3. 每条命令根据需要可以进行缩进或换行；建议关键字单独一行。
4. 注释
   * 单行注释：#注释文字
   * 单行注释： -- 注释文字
   * 多行注释： /* 注释文字 */

****

## DQL语言

### 基础查询

​	<!--查询前先使用 `use 库名;` 进入要查询的库-->

* 语法：1.`select 查询列表 from 表名(table);`   

  ​		           2.`select 查询列表, 查询列表, 。。。 from 表名(table)`; 

  ​			         3.`select  *  from 表名(table)；`     
 4. 查询常量值`select +"常量";`

 5. 查询表达式，例如`99*3`

 6. 查询函数/方法；

 

  + 2：按照输入的列表顺序查询显示
  + 3：只能按照数据库中的原始顺序查询显示列表		

* 特点：

  * 查询列表可以是：表中的字段、常量值、表达式、函数
  * 查询的结果是一个虚拟的表格
* 用着重号(esc下方那个)用于区分关键字或普通字段。
* 在可视化图形用户界面中，选中要执行的命令后再执行。

### 进阶查询

#### 模糊查询

* 语法：	` select 查询列表 from 表名 where 筛选条件;` 

* 分类： 

  * 按条件表达式筛选：条件运算符：>, <, =, !=, <>[^2]，>=, <=

  * 按逻辑表达式筛选：逻辑运算符：&&, ||, !, and, or, not[^3]

  * 模糊查询： like, between and, in, is null 

    * like:例如：` select 查询列表 from 表名 where studentName like '%a%'`[^4]
      1. 一般和通配符一起使用
      
         1. 通配符：'%'任意多个字符，包含0个；'_' 任意单个字符
      2. 转义：使用 \可对特殊符号进行转义[^5]	，但推荐使用mysql语法 ’escape关键字‘ 进行转义：`select 查询列表 from 表名 where studentName like '_$_%' escape '$'`[^6]

     * between  and示例:`select * from city where id between 12 and 30`[^7]
       	* between and 两边的数字不能颠倒
          	* 范围包括两边的临界
    	* in示例：`select * from city where CountryCode in ('CN','ASB');   `[^8]
    	* is null示例：`select *from city where name is null;`[^9]
     * 额外补充：`<=>`:安全等于,可以直接  `<=> null` 判断为null的字段,此外还可作为 普通 = 使用；

#### 排序查询

* 基础语法：`SELECT 查询列表 FROM 表名 WHERE 筛选条件 ORDDER BY 排序的列名 排序方式`[^10]
* ORDER BY 后面支持添加别名，表达式，函数
* 按多个字段排序：示例：`SELECT *
                        FROM employees
                        ORDER BY salary ASC,employee_id DESC;`[^11]

#### 分组查询

* ```mysql
  #添加f前的
  #可以使用group by 子句将表中的数据分成若干组
  #简单筛选
  select 分组函数，列（要求出现在group by的后面）
  from  表
  where 【筛选条件】
  group by 列
  order by 【子句】;
  ```
* 
  ```mysql
  #添加分组后的筛选条件
  #复杂筛选，示例：
  #查询人数大于2的部门
  
  select count(1),department_id
  from employees
  group by department_id
  having count(1)>2;#在上面第一步筛选出所有部门的人数的结果基础上筛选出人数大于2的;
  ```
  
* 

### 起别名

* 语法：
  * `select 100%98 as  结果`
  * `select last_name as 姓，last_name as 名 from 表名`
  * `select last_name 姓，first_name 名 from employees;`
* 好处：
  * 便于理解
  * 如果要查询的字段有重名的情况使用别名可以区分开来

### 常见函数

* 调用语法：`SELECT 函数名（实参列表）【FROM 表】`

* 分类：
  * 单行函数，如：concat(),length().ifnull()等
    * 字符函数
      1. length():返回参数的字节长度;
      2. concat(),拼接函数：`CONCAT('first_name,'last_name')`结果为：‘first_nameLast_name’
      3. upper()、lower():返回参数的大写/小写形式;
      4. substr():索引从 1 开始，而不是0,该函数有多个重载形式：
         1. substr(String str,int start):从 start 位置开始到str结束，返回一个截取后的字段
         2. substr(String str,int start,int length):从 strat位置开始截取长度为length的字段，返回截取后的字段
      5. insrt(String str1,String str2):返回str2在str1中第一次出现的位置 ,若找不到则返回0；
      6. trim(String str):去除str中的某些字符
         1. trim(      str    ):去除前后的空格
         2. trim('a' from aaaaaaaastraaaaaaaaaa):去除前后的    ’a‘；但并不能去除 str 里的 ‘a’
      7. lpad(String str,int length,String ch):用指定的 ch 字符或字符串在 str 字段左方填充使整个字段长度为 length；
         1. 若给定str字符串长度超过给定length则截断；
      8. rpad():效果同lpad，从右方开始填充；
      9. replace(String str,String old,String new ):替换函数，全部替换；
      
    * 数学函数
      1. round(number):对number进行四舍五入；
         1. 对round()进行重载：round(number,int n):保留n位小数
      2. ceil(number):向上取整；
      3. floor(number):向下取整；
      4. truncate(number,int n):截断，将给定的number截断为n位；
      5. mod(int n1,int n2):取余函数，返回n1/n2的余数；
      
    * 日期函数

      1. now():返回当前系统日期+时间；

      2. curdate():返回当前系统日期，不包括时间;

      3. curtime():返回当前时间，不包括日期;

      4. 获取给定日期的某一部分：,例如：`select year(datetime data)`

         1. `select year(now())`
         2. `select year(2021-5-24)`
         3. `select year(hiredate) from employees`[^12]
         4. 获取给定日期的月份且以英文显示：`monthname(datetime);`

      5. str_to_date(String date,String rule):将日期格式的字符转换成日期格式

         1. 例如`str_to_date('9-12-2001','%m-%d-%Y')`返回日期类型数据 '2001-09-13';

         2. 即将给定的日期按照给定的格式解析，最后返回一个标准格式的日期类型;

         3. | 序号 | 格式符 | 功能[^13]           |
            | ---- | ------ | ------------------- |
            | 1    | %Y     | 四位的年份          |
            | 2    | %y     | 两位的年份          |
            | 3    | %m     | 月份(01,02,03...12) |
            | 4    | %c     | 月份(1,2,3...11,12) |
            | 5    | %d     | 日(01,02....)       |
            | 6    | %H     | 小时(24小时制)      |
            | 7    | %h     | 小时(12小时制)      |
            | 8    | %i     | 分钟(00,01,02....)  |
            | 9    | %s     | 秒(00,01,02....59)  |

      6. date_format(datetime date,'String rule'):将给定的日期按照给定的给定的格式输出;

      7. datediff(datetime d1,datetime d2):返回日期 d1 到 d2 之间的相差天数;

    * 其他函数【补充】

      1. version():查看当前版本；
      2. database():查看当前数据库;
      3. user():查看当前用户;

    * 流程控制函数【补充】[^14]

      1. if():实现 if else 的效果：`if(obj,rusult1,result2)`:若obj为true，则返回result1，否则返回result2;

      2. case():

         1. ```mysql
            #类似 java 中 switch case 的用法:
            case 要判断的字段或表达式
            when 常量1 then 要显示的值1或语句1;#若显示值，则不用加分号
            when 常量2 then 要显示的值2或语句2;
            ··········
            else 要显示的值或语句;
            end
            #若搭配select使用，then后面只能显示值，若作为独立语句使用，则可以在then后面添加语句;
            ```

         2. ```mysql
            #类似 java 中的多重 if 的用法，但不完全一样
            case 
            when 条件1 then 要显示的值1或语句1;#若显示值，则不用加分号
            when 条件2 then 要显示的值2或语句;
            ···············
            else 要显示的值或语句
            end
            #若搭配select使用，then后面只能显示值，若作为独立语句使用，则可以在then后面添加语句;
            #若满足某个条件就执行then后的内容
            ```

  * 分组函数，做统计使用，又称为统计函数、聚合函数、组函数

    * 分类：sum求和，avg平均值，max最大值，min最小值，count计算个数，等
    * 简单使用：
      1. 以sum为例：`select sum(salary) from employees`,返回salary之和;
    * 参数支持类型 
      1. sum():只支持数值，其他类型不会报错，但没有意义，忽略 null
      2. avg()：同上
      3. max(),min():字符串也可以作为参数传入，即按照字母排序，取最大和最小;
      4. count():几乎可以传入任何参数，数值为 null 的不计入
    * 和distinct搭配去重：例如`sum(distinct salary)`
    * count()函数的详细介绍
      1. `select count (*) from employees;`：统计数据库中的总行数;
      2. `select count(obj) from employees;`:统计数据库中的总行数；[^15]
      3. 关于效率问题：在MYISAM存储引擎下，count(\*)的效率更高；而在INNODB存储引擎下，count(\*)和count(1)效率差不多，比count(String str)要高一些;
    * 和分组函数一同查询的字段要求是group by后的字段[^16]



****

[^自带客户端]: Commnd line client
[^h]: host的简称，主机名
[^P]: port，端口号
[^1]: 密码，直接填或回车后再填都行
[^2]: 又小又大，即不等,相对于 != 更推荐使用 <> 符号；
[^3]:相较于 &&，||，！，mysql中更推荐使用 and，or，not;
[^4]: 查询 “studentName”中含有 ‘a’ 的字段，其中%代表通配符，类似于 java正则表达式中的 ‘ * ’，前后各一个表示前面又任意字符且后面又任意字符;
[^5]: 类似 java 中的转义符 如：\% 即表示%;
[^6]: 示例中使用'$'作为转义符号，对_进行转义;

[^7]: 实例中，类似 id>=12 && id<=30， 在city中查询 id在12到30之间;
[^8]: 示例中，查找 countryCode为 ‘CN’和‘ASB’的字段，类似于:······where CountryCode = 'CN' or CountryCode = 'ASB';
[^9]:示例中，查找 name 为null的城市，若改写成 is not null 则查询 name 不为null 的城市，mysql语法中不支持 name = null 或 name ！= null 或 name <> null 的写法;
[^10]: asc 或 desc 升序或降序，asc可以省略，即默认为升序;
[^11]:先按 salary升序排列，之后若有salary数值相同的，再用 employee_id降序排列;
[^12]: 示例用法中的 ‘year’ 可替换为 ‘month’，‘day’，‘hour’等等，时间单位，括号内参数为日期型数据;
[^13]: 产生多行表格：在最后一个表格出按 `ctrl+enter`即可;
[^14]: 用于实现流程控制的函数;
[^15]: obj可为任何数值，一般为 1 ，原理为在数据库最前面再加上一列，填满 obj后统计obj的个数，从而计算出数据库中的总行数;
[^16]: group by现阶段还没学习！这句话大致意思为查询结果为一个规则的表格，不能用单行函数跟分组函数一起使用;
