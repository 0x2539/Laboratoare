<%@ Page Language="C#" %>
<html>
<head>
  <title>Forms Authentication - Default Page</title>
</head>

<script runat="server">

    int userId;

  void Page_Load(object sender, EventArgs e)
  {
      if (Context.User.Identity.IsAuthenticated)
      {
          Welcome.Text = "Hello, " + Context.User.Identity.Name;

          ButtonProfile.Visible = true;
          ButtonSignOut.Visible = true;
          ButtonSignIn.Visible = false;

          userId = getUserId();
      }
      else
      {
          Welcome.Text = "Hello, not authenticated";

          ButtonProfile.Visible = false;
          ButtonSignOut.Visible = false;
          ButtonSignIn.Visible = true;
      }
  }

  int getUserId()
  {
      if (Context.User.Identity.IsAuthenticated)
      {
          try
          {
              System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
              con.Open();
              string strQuery = "select [Id] from [dbo].[users] where [username]=@username";
              System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
              cmd.Parameters.AddWithValue("@username", System.Data.SqlDbType.Int).Value = Context.User.Identity.GetUserName();
              System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

              if (myReader.Read())
              {
                  // Assuming your desired value is the name as the 3rd field
                  int id = -1;
                  int.TryParse(myReader["Id"].ToString(), out id);
                  myReader.Close();
                  con.Close();
                  return id;
              }

              myReader.Close();
              con.Close();
          }
          catch (Exception ex)
          {
              System.Diagnostics.Debug.WriteLine(ex.ToString());
          }
      }
      return -1;
  }

  void Profile_Click(object sender, EventArgs e)
  {
      Response.Redirect("MyProfile.aspx?userId=" + userId);
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
        <asp:Button ID="ButtonSignIn" runat="server" Text="Sign In" style="float:right; margin:10px" OnClick="SignIn_Click"/>
        <asp:Button ID="ButtonProfile" runat="server" Text="Profile" style="float:right; margin:10px" OnClick="Profile_Click"/>
        <asp:Button ID="ButtonSignOut" runat="server" Text="Sign Out" style="float:right; margin:10px" OnClick="SignOut_Click"/>
      </h3>
  <asp:Label ID="Welcome" runat="server" />
      <p>
  </form>
</body>
</html>