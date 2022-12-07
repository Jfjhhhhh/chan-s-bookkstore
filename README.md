# chan-s-bookstore
#
# 程序功能：
######        构建三个系统，记录账户、图书、日志相关信息。读入指令，判断指令是否合法，并进行对应操作。
#
# 主体逻辑：
######

#
# 代码文件结构：
#
# 类的接口与成员：
- 图书类 (BOOK)
  - [ISBN]
  - [BookName], [Author]：图书名字，图书作者名字；
  - [Keyword]：图书关键词；
  - [Quantity]：购买数量；
  - [Price], [TotalCost]：图书单价，交易总额。
- 账户类 (ACCOUNT)
  - [Username]
  - [UserID], [Password], [CurrentPassword], [NewPassword]
  - [Privilege]
- 日志类 (LOG)
  - 交易笔数
  - 交易记录
  - 生成日志

