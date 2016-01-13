<%@ Page Language="C#" AutoEventWireup="true" CodeFile="NewPhoto.aspx.cs" Inherits="NewPhoto" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>

<script runat="server">
        
    int userId;
    int albumId = -1;

    void Page_Load(object sender, EventArgs e)
    {
        int.TryParse(Request.QueryString["albumId"], out albumId);
        userId = getUserId();

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
                string strQuery = "insert into [dbo].[photos] ([photoType], [photo], [album], [category], [description], [user]) values (@photoType, @photo, @albumId, @category, @description, @userId);SELECT CAST(scope_identity() AS int)";
                System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
                cmd.Parameters.Add("@photoType", System.Data.SqlDbType.VarChar).Value = ext;//contenttype;
                cmd.Parameters.Add("@photo", System.Data.SqlDbType.Binary).Value = bytes;
                cmd.Parameters.Add("@albumId", System.Data.SqlDbType.Int).Value = albumId;
                cmd.Parameters.Add("@category", System.Data.SqlDbType.VarChar).Value = CategoryTextBox.Text;
                cmd.Parameters.Add("@description", System.Data.SqlDbType.VarChar).Value = DescriptionTextBox.Text;
                cmd.Parameters.Add("@userId", System.Data.SqlDbType.Int).Value = userId;
                cmd.ExecuteNonQuery();
                con.Close();

                //InsertUpdateData(cmd);
                Status.ForeColor = System.Drawing.Color.Green;
                Status.Text = "File Uploaded Successfully";

                Response.Redirect("~/Album?albumId=" + albumId);
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
  
</script>

<body>

    <form runat="server">
        <div>
            <asp:Label ID="Status" runat="server" Text="Upload" />

            <input id="FileUpload1" type="file" runat="server" class="Cntrl1" />
            <asp:Button ID="btnUpload" runat="server" Text="Upload"
                OnClick="btnUpload_Click" />
            <div>
                Category:<asp:TextBox ID="CategoryTextBox" runat="server" />
                <asp:RequiredFieldValidator ID="RequiredFieldValidator1"
                    ControlToValidate="CategoryTextBox"
                    Display="Dynamic"
                    ErrorMessage="Cannot be empty."
                    runat="server" />
            </div>

            <div>
                Description:
                <asp:TextBox ID="DescriptionTextBox" runat="server" />
                <asp:RequiredFieldValidator ID="RequiredFieldValidator2"
                    ControlToValidate="DescriptionTextBox"
                    Display="Dynamic"
                    ErrorMessage="Cannot be empty."
                    runat="server" />
            </div>

        </div>
    </form>


    <link href='../css/jquery.guillotine.css' media='all' rel='stylesheet'>
    <link href='demo.css' media='all' rel='stylesheet'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0, target-densitydpi=device-dpi'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">

    <div id='content' style="display:none">
        <div class='frame'>
            <asp:Image ID="uploadedImage" runat="server" ImageUrl="~/Assets/empty_image.jpg" style="width:100%" />
        </div>
    </div>


</body>
</html>
