<%@ Page Language="C#" %>
<%@ Import Namespace="System.Web.Security" %>

<script runat="server">
    void Page_Load(object sender, EventArgs e)
    {
        if (Context.User.Identity.IsAuthenticated)
        {
            Response.Redirect("Default.aspx");
        }
    }

    void Logon_Click(object sender, EventArgs e)
    {
        SubmitRegister.Enabled = false;
        SubmitLogin.Enabled = false;
        try
        {
            if (login())
            {

                //  }
                //if ((UserEmail.Text == "jchen@contoso.com") && 
                //        (UserPass.Text == "37Yj*99Ps"))
                //  {
                FormsAuthentication.RedirectFromLoginPage(UserEmail.Text, Persist.Checked);
                Response.Redirect("Default.aspx");
                //Msg.Text = "Valid credentials.";
            }
            else
            {
                Msg.Text = "Invalid credentials. Please try again.";
            }
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine(ex.ToString());
        }
        SubmitRegister.Enabled = true;
        SubmitLogin.Enabled = true;
    }

  void Register_Click(object sender, EventArgs e)
  {
      SubmitRegister.Enabled = false;
      SubmitLogin.Enabled = false;
      try
      {
          if (!userExists())
          {
              System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
              con.Open();
              //insert the file into database
              string strQuery = "insert into [dbo].[users]([username], [password]) values (@username, @password)";
              System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
              cmd.Parameters.Add("@username", System.Data.SqlDbType.VarChar).Value = UserEmail.Text;
              cmd.Parameters.Add("@password", System.Data.SqlDbType.VarChar).Value = UserPass.Text;
              cmd.ExecuteNonQuery();
              con.Close();

              FormsAuthentication.RedirectFromLoginPage(UserEmail.Text, Persist.Checked);
              Response.Redirect("Default.aspx");
          }
          else
          {
              Msg.Text = "User already exists.";
          }
      }
      catch (Exception ex)
      {
          System.Diagnostics.Debug.WriteLine(ex.ToString());
      }
      SubmitRegister.Enabled = true;
      SubmitLogin.Enabled = true;
  }

  Boolean login()
  {
      try
      {
          //System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=.\SQLEXPRESS;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;User Instance=True;");
          System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
          //String strConnString = System.Configuration.ConfigurationManager.ConnectionStrings["PhotoDBContext"].ConnectionString;
          //System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(strConnString);
          con.Open();
          //insert the file into database
          string strQuery = "select [username] from [dbo].[users] where username=@username and password=@password";
          System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
          cmd.Parameters.AddWithValue("@username", System.Data.SqlDbType.VarChar).Value = UserEmail.Text;
          cmd.Parameters.AddWithValue("@password", System.Data.SqlDbType.VarChar).Value = UserPass.Text;
          System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

          if (myReader.Read())
          {
              // Assuming your desired value is the name as the 3rd field
              myReader.Close();
              con.Close();
              return true;
          }

          myReader.Close();
          con.Close();
      }
      catch (Exception ex)
      {
          System.Diagnostics.Debug.WriteLine(ex.ToString());
      }
      return false;
  }

  Boolean userExists()
  {
      try
      {
          //System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=.\SQLEXPRESS;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;User Instance=True;");
          System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
          //String strConnString = System.Configuration.ConfigurationManager.ConnectionStrings["PhotoDBContext"].ConnectionString;
          //System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(strConnString);
          con.Open();
          //insert the file into database
          string strQuery = "select [username] from [dbo].[users] where username=@username";
          System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
          cmd.Parameters.AddWithValue("@username", System.Data.SqlDbType.VarChar).Value = UserEmail.Text;
          System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

          if (myReader.Read())
          {
              // Assuming your desired value is the name as the 3rd field
              myReader.Close();
              con.Close();
              return true;
          }

          myReader.Close();
          con.Close();
      }
      catch (Exception ex)
      {
          System.Diagnostics.Debug.WriteLine(ex.ToString());
      }
      return false;
  }
</script>
<html>
<head id="Head1" runat="server">
  <title>Forms Authentication - Login</title>
</head>
<body>
  <form id="form1" runat="server">
    <h3>
      Logon Page</h3>
    <table>
      <tr>
        <td>
          E-mail address:</td>
        <td>
          <asp:TextBox ID="UserEmail" runat="server" /></td>
        <td>
          <asp:RequiredFieldValidator ID="RequiredFieldValidator1" 
            ControlToValidate="UserEmail"
            Display="Dynamic" 
            ErrorMessage="Cannot be empty." 
            runat="server" />
        </td>
      </tr>
      <tr>
        <td>
          Password:</td>
        <td>
          <asp:TextBox ID="UserPass" TextMode="Password" 
             runat="server" />
        </td>
        <td>
          <asp:RequiredFieldValidator ID="RequiredFieldValidator2" 
            ControlToValidate="UserPass"
            ErrorMessage="Cannot be empty." 
            runat="server" />
        </td>
      </tr>
      <tr>
        <td>
          Remember me?</td>
        <td>
          <asp:CheckBox ID="Persist" runat="server" /></td>
      </tr>
    </table>
    <asp:Button ID="SubmitLogin" OnClick="Logon_Click" Text="Log On" runat="server" />
    <asp:Button ID="SubmitRegister" OnClick="Register_Click" Text="Register" 
       runat="server" />
    <p>
      <asp:Label ID="Msg" ForeColor="red" runat="server" />
    </p>
  </form>
</body>
</html>