<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Album.aspx.cs" Inherits="Album" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
    
<script runat="server">
    void btnUpload_Click(object sender, EventArgs e)
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

            //insert the file into database
            string strQuery = "insert into [dbo].[photos]([photoType], [photo]) values (@photoType, @photo)";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery);
            cmd.Parameters.Add("@photoType", System.Data.SqlDbType.VarChar).Value = contenttype;
            cmd.Parameters.Add("@photo", System.Data.SqlDbType.Binary).Value = bytes;
            uploadedImage.ImageUrl = filePath;
            Status.Text = filePath;
            
            string base64String = Convert.ToBase64String(bytes, 0, bytes.Length);
            uploadedImage.ImageUrl = "data:image/jpg;base64," + base64String;
            uploadedImage.Visible = true;
            
            //InsertUpdateData(cmd);
            //Status.ForeColor = System.Drawing.Color.Green;
            //Status.Text = "File Uploaded Successfully";
        }
        else
        {
            //Status.ForeColor = System.Drawing.Color.Red;
            //Status.Text = "File format not recognised." +
            //  " Upload Image/Word/PDF/Excel formats";
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
</script>

<body>
    
      <asp:Label ID="Status" runat="server" Text="Upload" />
    <form id="form1" runat="server">
    <div>
    
    <asp:FileUpload ID="FileUpload1" runat="server" />
    <asp:Button ID="btnUpload" runat="server" Text="Upload"
                        OnClick="btnUpload_Click" />
        <asp:Image ID="uploadedImage" runat="server" ImageUrl="~/Assets/empty_image.jpg" Width="100" Height="100"/>
    </div>
    </form>
</body>
</html>
