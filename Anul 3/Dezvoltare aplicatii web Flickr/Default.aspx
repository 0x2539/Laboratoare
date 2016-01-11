﻿<%@ Page Language="C#" %>
<html>
<head>
  <title>Forms Authentication - Default Page</title>
</head>

<script runat="server">
  void Page_Load(object sender, EventArgs e)
  {
      if (Context.User.Identity.IsAuthenticated)
      {
          Welcome.Text = "Hello, " + Context.User.Identity.Name;

          ButtonProfile.Visible = true;
          ButtonSignOut.Visible = true;
          ButtonSignIn.Visible = false;
      }
      else
      {
          Welcome.Text = "Hello, not authenticated";

          ButtonProfile.Visible = false;
          ButtonSignOut.Visible = false;
          ButtonSignIn.Visible = true;
      }
  }

  void SignIn_Click(object sender, EventArgs e)
  {
    Response.Redirect("SignIn.aspx");
  }

  void SignOut_Click(object sender, EventArgs e)
  {
      FormsAuthentication.SignOut();
      Response.Redirect("Default.aspx");
  }
</script>

<body>
  <form id="Form1" runat="server">
  <h3>
    Using Forms Authentication
      <asp:Button ID="ButtonSignIn" runat="server" Text="Sign In" style="float:right" OnClick="SignIn_Click"/>
      <asp:Button ID="ButtonProfile" runat="server" Text="Profile" style="float:right"/>
    <asp:Button ID="ButtonSignOut" OnClick="SignOut_Click" 
       Text="Sign Out" runat="server" style="float:right"/>
      </h3>
  <asp:Label ID="Welcome" runat="server" />
      <p>
  </form>
</body>
</html>