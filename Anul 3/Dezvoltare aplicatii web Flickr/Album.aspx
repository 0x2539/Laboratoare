<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Album.aspx.cs" Inherits="Album" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
    
<script runat="server">

    int currentId = -1;

    void Page_Load(object sender, EventArgs e)
    {
        int.TryParse(Request.QueryString["albumId"], out currentId);
        if (albumIsValid())
        {
            if (!IsPostBack)
            {
                AlbumNameTextBox.Text = getAlbumName();
            }
        }
        else
        {
            AlbumNameTextBox.Text = "Invalid";
        }
    }
    
    Boolean albumIsValid()
    {

        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "select [name] from [dbo].[albums] where [Id]=@id";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = currentId;
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
    
    String getAlbumName()
    {

        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "select [name] from [dbo].[albums] where [Id]=@id";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = currentId;
            System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

            if (myReader.Read())
            {
                // Assuming your desired value is the name as the 3rd field
                String name = myReader["name"].ToString();
                myReader.Close();
                con.Close();
                return name;
            }

            myReader.Close();
            con.Close();
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine(ex.ToString());
        }
        return "";
    }

    void btnUpload_Click(object sender, EventArgs e)
    {
        if (CategoryTextBox.Text.Length > 0 && DescriptionTextBox.Text.Length > 0)
        {
            // Read the file and convert it to Byte Array
            string filePath = FileUpload1.PostedFile.FileName;
            string filename = System.IO.Path.GetFileName(filePath);
            string ext = System.IO.Path.GetExtension(filename);
            string contenttype = String.Empty;

            //Set the contenttype based on File Extension
            switch (ext)
            {
                case ".doc":
                    contenttype = "application/vnd.ms-word";
                    break;
                case ".docx":
                    contenttype = "application/vnd.ms-word";
                    break;
                case ".xls":
                    contenttype = "application/vnd.ms-excel";
                    break;
                case ".xlsx":
                    contenttype = "application/vnd.ms-excel";
                    break;
                case ".jpg":
                    contenttype = "image/jpg";
                    break;
                case ".png":
                    contenttype = "image/png";
                    break;
                case ".gif":
                    contenttype = "image/gif";
                    break;
                case ".pdf":
                    contenttype = "application/pdf";
                    break;
            }
            if (contenttype != String.Empty)
            {

                System.IO.Stream fs = FileUpload1.PostedFile.InputStream;
                System.IO.BinaryReader br = new System.IO.BinaryReader(fs);
                Byte[] bytes = br.ReadBytes((Int32)fs.Length);

                uploadedImage.ImageUrl = filePath;
                Status.Text = filePath;

                string base64String = Convert.ToBase64String(bytes, 0, bytes.Length);
                uploadedImage.ImageUrl = "data:image/" + ext + ";base64," + base64String;
                uploadedImage.Visible = true;

                System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
                con.Open();
                //insert the file into database
                string strQuery = "insert into [dbo].[photos] ([photoType], [photo], [album], [category], [description]) values (@photoType, @photo, @albumId, @category, @description)";
                System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
                cmd.Parameters.Add("@photoType", System.Data.SqlDbType.VarChar).Value = ext;//contenttype;
                cmd.Parameters.Add("@photo", System.Data.SqlDbType.Binary).Value = bytes;
                cmd.Parameters.Add("@albumId", System.Data.SqlDbType.Int).Value = currentId;
                cmd.Parameters.Add("@category", System.Data.SqlDbType.VarChar).Value = CategoryTextBox.Text;
                cmd.Parameters.Add("@description", System.Data.SqlDbType.VarChar).Value = DescriptionTextBox.Text;
                cmd.ExecuteNonQuery();
                con.Close();

                //InsertUpdateData(cmd);
                Status.ForeColor = System.Drawing.Color.Green;
                Status.Text = "File Uploaded Successfully";
            }
            else
            {
                Status.ForeColor = System.Drawing.Color.Red;
                Status.Text = "File format not recognised." +
                  " Upload Image/Word/PDF/Excel formats";
            }
        }
        else
        {
            Status.ForeColor = System.Drawing.Color.Red;
            Status.Text = "Complete category";
        }
    }
  
    private Boolean InsertUpdateData(System.Data.SqlClient.SqlCommand cmd)
    {
        String strConnString = System.Configuration.ConfigurationManager.ConnectionStrings["conString"].ConnectionString;
        System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(strConnString);
        cmd.CommandType = System.Data.CommandType.Text;
        cmd.Connection = con;
        try
        {
            con.Open();
            cmd.ExecuteNonQuery();
            return true;
        }
        catch (Exception ex)
        {
            Response.Write(ex.Message);
            return false;
        }
        finally
        {
            con.Close();
            con.Dispose();
        }
    }
    
    void AlbumNameTextBox_TextChanged(object sender, EventArgs e)
    {
    }

    void ButtonSaveAlbumName_Click(object sender, EventArgs e)
    {
        System.Diagnostics.Debug.WriteLine("clicked " + AlbumNameTextBox.Text + " " + AlbumNameTextBox.Text.Length);
        if (AlbumNameTextBox.Text.Length > 0)
        {
            try
            {
                System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
                con.Open();
                //insert the file into database
                string strQuery = "update [dbo].[albums] set [name]=@name where [Id]=@id";
                System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
                cmd.Parameters.Add("@name", System.Data.SqlDbType.VarChar).Value = AlbumNameTextBox.Text;
                cmd.Parameters.Add("@id", System.Data.SqlDbType.Int).Value = currentId;
                //System.Data.SqlClient.SqlParameter theId = cmd.Parameters.Add("@[Id]", System.Data.SqlDbType.Int);
                //theId.Direction = System.Data.ParameterDirection.Output;
                cmd.ExecuteNonQuery();
                con.Close();
                //id = Convert.ToInt64(theId.Value);
            }
            catch (Exception ex)
            {
                //Response.Write(ex.Message);
                System.Diagnostics.Debug.WriteLine(ex.ToString());
            }
        }
        else
        {
        }
    }
</script>

<body>
    
    <form id="form1" runat="server" defaultbutton="DoNothing">
        <asp:Button ID="DoNothing" runat="server" Enabled="false" style="display: none;" />
            <div>
            <asp:Panel ID="Panel1" runat="server" DefaultButton="ButtonSaveAlbumName">
                <asp:TextBox ID="AlbumNameTextBox" runat="server"></asp:TextBox>
                <asp:Button ID="ButtonSaveAlbumName" runat="server" onclick="ButtonSaveAlbumName_Click" style="display:none"/>
            </asp:Panel>
        </div>
    
      <asp:Label ID="Status" runat="server" Text="Upload" />
    <div>
    
        <asp:FileUpload ID="FileUpload1" runat="server" />
        <asp:Button ID="btnUpload" runat="server" Text="Upload"
                            OnClick="btnUpload_Click" />
            <asp:Image ID="uploadedImage" runat="server" ImageUrl="~/Assets/empty_image.jpg" Width="100" Height="100"/>
        <div>
            
          <asp:TextBox ID="CategoryTextBox" runat="server" />
          <asp:RequiredFieldValidator ID="RequiredFieldValidator1" 
            ControlToValidate="CategoryTextBox"
            Display="Dynamic" 
            ErrorMessage="Cannot be empty." 
            runat="server" />
        </div>
        
        <div>
            
          <asp:TextBox ID="DescriptionTextBox" runat="server" />
          <asp:RequiredFieldValidator ID="RequiredFieldValidator2" 
            ControlToValidate="DescriptionTextBox"
            Display="Dynamic" 
            ErrorMessage="Cannot be empty." 
            runat="server" />
        </div>

    </div>
    </form>
</body>
</html>
