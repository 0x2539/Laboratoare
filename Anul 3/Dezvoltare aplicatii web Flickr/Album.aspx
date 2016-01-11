<%@ Page Language="C#" MasterPageFile="~/MasterPageAlbum.master" AutoEventWireup="true" CodeFile="Album.aspx.cs" Inherits="Album" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
    
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
            loadPhotos();
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

    private void loadPhotos()
    {
        System.Diagnostics.Debug.WriteLine("getting list");
        List<Models.PhotoDB> list = getPhotos();
        System.Diagnostics.Debug.WriteLine("got list");

        XElement xml = new XElement("Photos");

        System.Xml.XmlDocument doc = new System.Xml.XmlDocument();
        doc.LoadXml("<Photos></Photos>");
        System.Xml.XmlNode rootNode = doc.SelectSingleNode("Photos");
        
        System.Diagnostics.Debug.WriteLine("list size: " + list.Count);
        foreach(Models.PhotoDB photo in list) {

            System.Diagnostics.Debug.WriteLine("list item: " + photo.ID);

            System.Xml.XmlAttribute xmlPhotoId = doc.CreateAttribute("Id");
            xmlPhotoId.Value = photo.ID.ToString();
            
            System.Xml.XmlAttribute xmlphotoType = doc.CreateAttribute("photoType");
            xmlphotoType.Value = photo.PhotoType;
            
            System.Xml.XmlAttribute xmlPhoto = doc.CreateAttribute("photo");
            xmlPhoto.Value = photo.Photo;
            
            System.Xml.XmlAttribute xmlCategory = doc.CreateAttribute("category");
            xmlCategory.Value = photo.Category;
            
            System.Xml.XmlAttribute xmlDescription = doc.CreateAttribute("description");
            xmlDescription.Value = photo.Description;
            //XAttribute xmlPhotoPhotoType = new XAttribute("photoType", photo.PhotoType);
            //XAttribute xmlPhotoPhoto = new XAttribute("photo", photo.Photo);
            //XAttribute xmlPhotoCategory = new XAttribute("category", photo.Category);
            //XAttribute xmlPhotoDescription = new XAttribute("description", photo.Description);
            //XElement xmlPhoto = new XElement("Photo", xmlPhotoId, xmlPhotoPhotoType, xmlPhotoPhoto, xmlPhotoCategory, xmlPhotoDescription);
            //xml.Add(xmlPhoto);
            //System.Diagnostics.Debug.WriteLine(xmlPhoto.ToString());

            System.Xml.XmlNode xmlNode = doc.CreateNode(System.Xml.XmlNodeType.Element, "Photo", "");
            xmlNode.Attributes.Append(xmlPhotoId);
            xmlNode.Attributes.Append(xmlphotoType);
            xmlNode.Attributes.Append(xmlPhoto);
            xmlNode.Attributes.Append(xmlCategory);
            xmlNode.Attributes.Append(xmlDescription);
            rootNode.AppendChild(xmlNode);
        }
        
        System.Diagnostics.Debug.WriteLine(xml.ToString());
        System.Diagnostics.Debug.WriteLine(xml.Value);
        System.Diagnostics.Debug.WriteLine("file: " + doc.InnerXml);
        
        System.Xml.XmlDocument xDoc = new System.Xml.XmlDocument();
        //xDoc.LoadXml(xml.Value);

        XDSPhoto.Data = doc.InnerXml;
        XDSPhoto.DataBind();
        //XDSMovie.Data
    }
    
    private List<Models.PhotoDB> getPhotos()
    {
        List<Models.PhotoDB> photosList = new List<Models.PhotoDB>();

        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "select * from [dbo].[photos] where [album]=@id";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = currentId;
            System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

            if (myReader.Read())
            {
                photosList.Add(readerToPhotoDB(myReader));
                System.Diagnostics.Debug.WriteLine("getting item " + readerToPhotoDB(myReader).ID);
            }

            myReader.Close();
            con.Close();
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine(ex.ToString());
        }
        return photosList;
    }

    private Models.PhotoDB readerToPhotoDB(System.Data.SqlClient.SqlDataReader myReader)
    {
        Models.PhotoDB newPhoto = new Models.PhotoDB();
        
        newPhoto.ID = int.Parse(myReader["Id"].ToString());
        newPhoto.PhotoType = myReader["photoType"].ToString();
        newPhoto.Category = myReader["category"].ToString();
        newPhoto.Description = myReader["description"].ToString();

        //considering "photo's" bytes are on 2nd column
        byte[] Photo = (byte[])myReader.GetValue(2);

        string base64String = Convert.ToBase64String(Photo, 0, Photo.Length);
        newPhoto.Photo = base64String;
        
        return newPhoto;
    }
    
    /*private void loadPhotos(object sender, EventArgs e)
    {
        System.Xml.XmlTextWriter writer = new System.Xml.XmlTextWriter("product.xml", System.Text.Encoding.UTF8);
        writer.WriteStartDocument(true);
        writer.Formatting = Formatting.Indented;
        writer.Indentation = 2;
        writer.WriteStartElement("Table");
        createNode("1", "Product 1", "1000", writer);
        createNode("2", "Product 2", "2000", writer);
        createNode("3", "Product 3", "3000", writer);
        createNode("4", "Product 4", "4000", writer);
        writer.WriteEndElement();
        writer.WriteEndDocument();
        writer.Close();
        MessageBox.Show("XML File created ! ");
    }
    
    private void createNode(string pID, string pName, string pPrice, System.Xml.XmlTextWriter writer)
    {
        writer.WriteStartElement("Product");
        writer.WriteStartElement("Product_id");
        writer.WriteString(pID);
        writer.WriteEndElement();
        writer.WriteStartElement("Product_name");
        writer.WriteString(pName);
        writer.WriteEndElement();
        writer.WriteStartElement("Product_price");
        writer.WriteString(pPrice);
        writer.WriteEndElement();
        writer.WriteEndElement();
    }*/
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

        <asp:XmlDataSource ID="XDSPhoto" runat="server" XPath="Photos/Photo"></asp:XmlDataSource>

        <asp:Repeater ID="Repeater1" runat="server" DataSourceID="XDSPhoto">
            <ItemTemplate>
                <div style="background-color: #cceeff; width: 460px; height:250px">
                    <div style="float: left; width: 140px; padding: 5px" DataSource='<%# XPathSelect("Photo") %>'>
                        <!--<img runat="server" id="MovieImg" width="120" height="190" src='<%# "~/Images/" + XPath("@ID") + ".jpg" %>' />-->
                        <asp:Image ID="Img1" runat="server" ImageUrl='<%# "data:image/" + XPath("@photoType") + ";base64," + XPath("@photo") %>' Width="100" Height="100"/>
                    </div>
                </div>
            </ItemTemplate>
            <SeparatorTemplate>
                <br />
            </SeparatorTemplate>
        </asp:Repeater>


</body>
</html>
    
</asp:Content>
