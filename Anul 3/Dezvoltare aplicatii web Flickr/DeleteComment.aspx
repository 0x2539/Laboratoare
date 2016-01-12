<%@ Page Language="C#" AutoEventWireup="true" CodeFile="DeleteComment.aspx.cs" Inherits="DeleteComment" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
    <script runat="server">

    int currentId = -1;
    int userId;

    void Page_Load(object sender, EventArgs e)
    {
        int.TryParse(Request.QueryString["commentId"], out currentId);
        userId = getUserId();
        if(userId == getPhotoOwner() || userId == getCommentOwner())
        {
            removeComment();
        }
        System.Diagnostics.Debug.WriteLine("useri: " + userId + " " + getPhotoOwner() + " " + getCommentOwner());
        Response.Redirect(Request.UrlReferrer.ToString());
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

    int getCommentOwner()
    {
        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "select [user] from [dbo].[comments] where [Id]=@id";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = currentId;
            System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

            if (myReader.Read())
            {
                // Assuming your desired value is the name as the 3rd field
                int id = -1;
                int.TryParse(myReader["user"].ToString(), out id);
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
        return -1;
    }
    
    int getPhotoOwner()
    {
            try
            {
                System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
                con.Open();
                string strQuery = "select [photo] from [dbo].[comments] where [Id]=@id";
                System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
                cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = currentId;
                System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

                if (myReader.Read())
                {
                    // Assuming your desired value is the name as the 3rd field
                    int id = -1;
                    int.TryParse(myReader["photo"].ToString(), out id);
                    myReader.Close();
                    con.Close();
                    
                    return getUserFromPhoto(id);
                }

                myReader.Close();
                con.Close();
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
            }
        return -1;
    }
    
    int getUserFromPhoto(int photoId)
    {
        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "select [user] from [dbo].[photos] where [Id]=@id";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = photoId;
            System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

            if (myReader.Read())
            {
                // Assuming your desired value is the name as the 3rd field
                int id = -1;
                int.TryParse(myReader["user"].ToString(), out id);
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
        return -1;
    }

    void removeComment()
    {
        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "delete from [dbo].[comments] where [Id]=@id";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.Add("@id", System.Data.SqlDbType.Int).Value = currentId;
            cmd.ExecuteNonQuery();
            con.Close();
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine(ex.ToString());
        }
    }
    
</script>
<body>
    <form id="form1" runat="server">
    <div>
    
    </div>
    </form>
</body>
</html>
