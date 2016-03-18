<%@ Page Language="C#" AutoEventWireup="true" CodeFile="SignOut.aspx.cs" Inherits="SignOut" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>

    <script runat="server">

        void Page_Load(object sender, EventArgs e)
        {
            FormsAuthentication.SignOut();
            Response.Redirect("Default.aspx");
        }
    </script>
</body>
</html>
