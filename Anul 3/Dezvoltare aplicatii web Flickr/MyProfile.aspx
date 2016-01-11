<%@ Page Language="C#" AutoEventWireup="true" CodeFile="MyProfile.aspx.cs" Inherits="MyProfile" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
    
<script runat="server">
    void btnNewAlbum_Click(object sender, EventArgs e)
    {
        Response.Redirect("Album.aspx?albumId=" + createNewAlbum().ToString());
        //btnNewAlbum.Text = createNewAlbum().ToString();
    }
    
    long createNewAlbum()
    {
        btnNewAlbum.Enabled = false;
        long id = -1;
        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            //insert the file into database
            string strQuery = "insert into [dbo].[albums] ([name]) values (@name);SELECT CAST(scope_identity() AS int)";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.Add("@name", System.Data.SqlDbType.VarChar).Value = " ";
            //System.Data.SqlClient.SqlParameter theId = cmd.Parameters.Add("@[Id]", System.Data.SqlDbType.Int);
            //theId.Direction = System.Data.ParameterDirection.Output;
            //cmd.ExecuteNonQuery();
            id = cmd.ExecuteScalar() != null ? (int)cmd.ExecuteScalar() : -2;
            con.Close();
            //id = Convert.ToInt64(theId.Value);
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine(ex.ToString());
        }
        btnNewAlbum.Enabled = true;
        return id;
    }
    
</script>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
<style>
* {
    box-sizing: border-box;
}
.row:after {
    content: "";
    clear: both;
    display: block;
}
[class*="col-"] {
    float: left;
    padding: 15px;
}
.col-1 {width: 8.33%;}
.col-2 {width: 16.66%;}
.col-3 {width: 25%;}
.col-4 {width: 33.33%;}
.col-5 {width: 41.66%;}
.col-6 {width: 50%;}
.col-7 {width: 58.33%;}
.col-8 {width: 66.66%;}
.col-9 {width: 75%;}
.col-10 {width: 83.33%;}
.col-11 {width: 91.66%;}
.col-12 {width: 100%;}
html {
    font-family: "Lucida Sans", sans-serif;
}
.header {
    background-color: #9933cc;
    color: #ffffff;
    padding: 15px;
}
.menu ul {
    list-style-type: none;
    margin: 0;
    padding: 0;
}
.menu li {
    padding: 8px;
    margin-bottom: 7px;
    background-color :#33b5e5;
    color: #ffffff;
    box-shadow: 0 1px 3px rgba(0,0,0,0.12), 0 1px 2px rgba(0,0,0,0.24);
}
.menu li:hover {
    background-color: #0099cc;
}
</style>
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
    <asp:Button ID="btnNewAlbum" runat="server" Text="New Album" OnClick="btnNewAlbum_Click" />
    </div>
    </form>

    <div class="row">
        <div class="col-3">col1</div>
        <div class="col-3">col2</div>
        <div class="col-3">col3</div>
        <div class="col-3">col4</div>
    </div>
</body>
</html>
