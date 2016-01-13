<%@ Page Language="C#" MasterPageFile="~/MasterPageAlbum.master" AutoEventWireup="true" CodeFile="Album.aspx.cs" Inherits="Album" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" runat="Server">

    <!DOCTYPE html>

    <html xmlns="http://www.w3.org/1999/xhtml">

    <script runat="server">

        int currentId = -1;
        int userId;
        int ownerId;

        void Page_Load(object sender, EventArgs e)
        {
            int.TryParse(Request.QueryString["albumId"], out currentId);
            userId = getUserId();

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

                System.Xml.XmlDocument doc = new System.Xml.XmlDocument();// XDSPhoto.GetXmlDocument();
                doc.LoadXml("<Photos></Photos>");

                doc.Save(Server.MapPath("~/App_Data/temp.xml"));
                //XDSPhoto.Data = doc.InnerXml;
                XDSPhoto.DataFile = Server.MapPath("~/App_Data/temp.xml");
                //XDSPhoto.Data = xDoc.InnerXml;
                XDSPhoto.DataBind();
                XDSPhoto.Save();
            }

            form1.Visible = canModify();
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

        Boolean albumIsValid()
        {

            try
            {
                System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
                con.Open();
                string strQuery = "select [user] from [dbo].[albums] where [Id]=@id";
                System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
                cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = currentId;
                System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

                if (myReader.Read())
                {
                    // Assuming your desired value is the name as the 3rd field
                    ownerId = int.Parse(myReader["user"].ToString());
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
            foreach (Models.PhotoDB photo in list)
            {

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

            //System.Xml.XmlDocument xDoc = new System.Xml.XmlDocument();
            //xDoc.LoadXml(xml.Value);

            doc.Save(Server.MapPath("~/App_Data/temp.xml"));
            //XDSPhoto.Data = doc.InnerXml;
            XDSPhoto.DataFile = Server.MapPath("~/App_Data/temp.xml");
            XDSPhoto.DataBind();
            XDSPhoto.Save();
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

                while (myReader.Read())
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


        Boolean canModify()
        {
            if (userId == ownerId)
            {
                return true;
            }
            return false;
        }

        void AddNewPhotoButton_Click(object sender, EventArgs e)
        {
            Response.Redirect("~/NewPhoto?albumId=" + currentId);
        }
    </script>

    <body>

        <form id="form1" runat="server" defaultbutton="DoNothing">
            <asp:Button ID="DoNothing" runat="server" Enabled="false" Style="display: none;" />
            <div>
                <asp:Panel ID="Panel1" runat="server" DefaultButton="ButtonSaveAlbumName">
                    Album's Name:<asp:TextBox ID="AlbumNameTextBox" runat="server"></asp:TextBox>
                    <asp:Button ID="ButtonSaveAlbumName" runat="server" OnClick="ButtonSaveAlbumName_Click" Style="display: none" />
                </asp:Panel>
            </div>

            <asp:Button ID="AddNewPhotoButton" runat="server" Text="Add new photo" OnClick="AddNewPhotoButton_Click" />
        </form>

        <link href='../css/jquery.guillotine.css' media='all' rel='stylesheet'>
        <link href='demo.css' media='all' rel='stylesheet'>
        <meta name='viewport' content='width=device-width, initial-scale=1.0, target-densitydpi=device-dpi'>
        <meta http-equiv="X-UA-Compatible" content="IE=edge">

        <asp:XmlDataSource ID="XDSPhoto" runat="server" XPath="Photos/Photo"></asp:XmlDataSource>

        <asp:Repeater ID="Repeater1" runat="server" DataSourceID="XDSPhoto">
            <ItemTemplate>

                <div id='content'>

                    <div class='frame'>
                        <a href='<%# "/Photo.aspx?photoId=" + XPath("@Id") %>'>
                            <img id="someImg" runat="server" datasource='<%# XPathSelect("Photo") %>' src='<%# "data:image/" + XPath("@photoType") + ";base64," + XPath("@photo") %>' />
                        </a>
                    </div>

                    <a href='<%# "/Search.aspx?search=" + XPath("@category") %>'>
                        <div id='category'><%#XPath("@category")%></div>
                    </a>

                    <div id='description'><%# XPath("@description") %></div>

                </div>

            </ItemTemplate>
            <SeparatorTemplate>
                <br />
            </SeparatorTemplate>
        </asp:Repeater>


    </body>
    </html>

</asp:Content>
