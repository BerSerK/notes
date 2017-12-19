VBA notes
+++++++++++++++++++++++++++++++

VBA 连接mysql
================================

.. code-block:: python

   Dim Sql As String
   Dim Con As ADODB.Connection
   Dim Rec As ADODB.Recordset
   Con.ConnectionString = "Driver={MySQL ODBC 5.3 Unicode Driver};" + _
   "Server=host;" + _
   "UID=username;" + _
   "PWD=password;" + _
   "OPTION=3;"
   Con.Open
   
   Sql = "select * From fee_details.ziguan where time_period = '" & TargetPeriod & "' and product_name = '" & .Cells(i, 4) & "';"
   Set Rec = New Recordset
   Set Rec = Con.Execute(Sql, , adCmdText)
   i = 1
   Do While Not Rec.EOF
       .Cells(i, 5) = Rec("management_fee")
       .Cells(i, 6) = Rec("hosting_fee")
       .Cells(i, 7) = Rec("service_fee")
       .Cells(i, 9) = Rec("other_fee")
       .Cells(i, 10) = Rec("performance_compensation")
       Rec.MoveNext
       i = i + 1
   Loop

  
OUTLOOK收到邮件后自动执行宏
=====================================================
`Stack Over Flow <https://stackoverflow.com/questions/11263483/how-do-i-trigger-a-macro-to-run-after-a-new-mail-is-received-in-outlook>`_

.. code-block:: python

    Private WithEvents Items As Outlook.Items
    Private Sub Application_Startup()
    Dim olApp As Outlook.Application
    Dim objNS As Outlook.NameSpace
    Set olApp = Outlook.Application
    Set objNS = olApp.GetNamespace("MAPI")
    ' default local Inbox
    Set Items = objNS.GetDefaultFolder(olFolderInbox).Items
    End Sub
    Private Sub Items_ItemAdd(ByVal item As Object)

    On Error Goto ErrorHandler
    Dim Msg As Outlook.MailItem
    If TypeName(item) = "MailItem" Then
    Set Msg = item
    ' ******************
    ' do something here
    ' ******************
    End If
    ProgramExit:
    Exit Sub
    ErrorHandler:
    MsgBox Err.Number & " - " & Err.Description
    Resume ProgramExit
    End Sub


把代码复制到模块 *ThisOutlookSession* 中，重启Outlook. 
		
