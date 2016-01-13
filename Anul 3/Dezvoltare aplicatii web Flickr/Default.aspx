<%@ Page Language="C#" MasterPageFile="~/MasterPageMaster.master" AutoEventWireup="true" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" runat="Server">

    <script runat="server">

        int userId;
        String selectedCategory;

        void Page_Load(object sender, EventArgs e)
        {
            selectedCategory = Request.QueryString["category"];
            if (Context.User.Identity.IsAuthenticated)
            {
                userId = getUserId();
            }
            else
            {
            }

            if (selectedCategory == null || selectedCategory.Length == 0)
            {
                categoryAll.Attributes["class"] = "active";
            }
            else
            {
                categoryAll.Attributes["class"] = "";
            }

            loadPhotos();
            loadCategories();
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


        private void loadPhotos()
        {
            List<Models.PhotoDB> list = getPhotos();

            System.Xml.XmlDocument doc = new System.Xml.XmlDocument();
            doc.LoadXml("<Photos></Photos>");
            System.Xml.XmlNode rootNode = doc.SelectSingleNode("Photos");

            System.Diagnostics.Debug.WriteLine("list size: " + list.Count);
            foreach (Models.PhotoDB photo in list)
            {
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

            //System.Xml.XmlDocument xDoc = new System.Xml.XmlDocument();
            //xDoc.LoadXml(xml.Value);

            doc.Save(Server.MapPath("~/App_Data/tempAll.xml"));
            //XDSPhoto.Data = doc.InnerXml;
            XDSPhoto.DataFile = Server.MapPath("~/App_Data/tempAll.xml");
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
                string strQuery;
                System.Data.SqlClient.SqlCommand cmd;
                if (selectedCategory != null && selectedCategory.Length > 0)
                {
                    strQuery = "select * from [dbo].[photos] where [category]=@category order by [Id] Desc";
                    cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
                    cmd.Parameters.Add("@category", System.Data.SqlDbType.VarChar).Value = selectedCategory;
                }
                else
                {
                    strQuery = "select * from [dbo].[photos] order by [Id] Desc";
                    cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
                }
                System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

                while (myReader.Read())
                {
                    photosList.Add(readerToPhotoDB(myReader));
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


        private void loadCategories()
        {
            List<String> list = getCategories();

            System.Xml.XmlDocument doc = new System.Xml.XmlDocument();
            doc.LoadXml("<Categories></Categories>");
            System.Xml.XmlNode rootNode = doc.SelectSingleNode("Categories");

            foreach (String category in list)
            {
                System.Xml.XmlAttribute xmlCategory = doc.CreateAttribute("category");
                xmlCategory.Value = category;

                System.Xml.XmlAttribute xmlSelected = doc.CreateAttribute("selected");
                if (category.Equals(selectedCategory))
                {
                    xmlSelected.Value = "active";
                }
                else
                {
                    xmlSelected.Value = "";
                }

                System.Xml.XmlNode xmlNode = doc.CreateNode(System.Xml.XmlNodeType.Element, "Category", "");
                xmlNode.Attributes.Append(xmlCategory);
                xmlNode.Attributes.Append(xmlSelected);
                rootNode.AppendChild(xmlNode);
            }

            doc.Save(Server.MapPath("~/App_Data/tempCategories.xml"));
            //XDSPhoto.Data = doc.InnerXml;
            XDSCategories.DataFile = Server.MapPath("~/App_Data/tempCategories.xml");
            XDSCategories.DataBind();
            XDSCategories.Save();
            //XDSMovie.Data
        }

        private List<String> getCategories()
        {
            List<String> photosList = new List<String>();

            try
            {
                System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
                con.Open();
                string strQuery = "select [category] from [dbo].[photos] group by [category]";
                System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
                System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

                while (myReader.Read())
                {
                    photosList.Add(readerToCategory(myReader));
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

        private String readerToCategory(System.Data.SqlClient.SqlDataReader myReader)
        {
            return myReader["category"].ToString();
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

    <link href="//maxcdn.bootstrapcdn.com/font-awesome/4.1.0/css/font-awesome.min.css" rel="stylesheet">
    <link href='../css/jquery.guillotine.css' media='all' rel='stylesheet'>
    <link href="thumbnail.css" media='all' rel='stylesheet'>
    <link href="verticalMenu.css" media='all' rel='stylesheet'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0, target-densitydpi=device-dpi'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">

    <ul class="verticalUl">

        <li class="verticalLi"><a href="/Default.aspx" runat="server" id="categoryAll">All</a></li>
        <asp:XmlDataSource ID="XDSCategories" runat="server" XPath="Categories/Category"></asp:XmlDataSource>

        <asp:Repeater ID="Repeater2" runat="server" DataSourceID="XDSCategories">
            <ItemTemplate>

                <li class="verticalLi"><a class='<%#XPath("@selected")%>' href='<%# "/Default.aspx?category=" + XPath("@category") %>'><%# XPath("@category") %></a></li>

            </ItemTemplate>
        </asp:Repeater>

    </ul>

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

</asp:Content>
