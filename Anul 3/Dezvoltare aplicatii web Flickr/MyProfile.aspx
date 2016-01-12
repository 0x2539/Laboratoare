<%@ Page Language="C#" MasterPageFile="~/MasterPageMyProfile.master" AutoEventWireup="true" CodeFile="MyProfile.aspx.cs" Inherits="MyProfile" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
    
<script runat="server">

    int userId;
    int currentId;

    void Page_Load(object sender, EventArgs e)
    {
        int.TryParse(Request.QueryString["userId"], out userId);
        
        if(userIsValid())
        {
            loadAlbums();
        }
        else
        {
            System.Xml.XmlDocument doc = new System.Xml.XmlDocument();// XDSPhoto.GetXmlDocument();
            doc.LoadXml("<Albums></Albums>");

            doc.Save(Server.MapPath("~/App_Data/tempAlbum.xml"));
            //XDSPhoto.Data = doc.InnerXml;
            XDSAlbums.DataFile = Server.MapPath("~/App_Data/tempAlbum.xml");
            //XDSPhoto.Data = xDoc.InnerXml;
            XDSAlbums.DataBind();
            XDSAlbums.Save();
        }
    }
    
    Boolean userIsValid()
    {
        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "select [username] from [dbo].[users] where [Id]=@id";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = userId;
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
    
    void btnNewAlbum_Click(object sender, EventArgs e)
    {
        Response.Redirect("Album.aspx?albumId=" + createNewAlbum().ToString());
        //btnNewAlbum.Text = createNewAlbum().ToString();
    }
    
    long createNewAlbum()
    {
        long id = -1;
        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            //insert the file into database
            string strQuery = "insert into [dbo].[albums] ([name], [user]) values (@name, @userId);SELECT CAST(scope_identity() AS int)";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.Add("@name", System.Data.SqlDbType.VarChar).Value = " ";
            cmd.Parameters.Add("@userId", System.Data.SqlDbType.Int).Value = userId;
            //System.Data.SqlClient.SqlParameter theId = cmd.Parameters.Add("@[Id]", System.Data.SqlDbType.Int);
            //theId.Direction = System.Data.ParameterDirection.Output;
            object response = cmd.ExecuteScalar();
            id = response != null ? (int)response : -2;
            con.Close();
            //id = Convert.ToInt64(theId.Value);
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine(ex.ToString());
        }
        return id;
    }


    void loadAlbums()
    {
        System.Diagnostics.Debug.WriteLine("getting list");
        List<Models.AlbumDB> list = getAlbums();
        System.Diagnostics.Debug.WriteLine("got list");

        System.Xml.XmlDocument doc = new System.Xml.XmlDocument();
        doc.LoadXml("<Albums></Albums>");
        System.Xml.XmlNode rootNode = doc.SelectSingleNode("Albums");

        System.Diagnostics.Debug.WriteLine("list size: " + list.Count);
        foreach (Models.AlbumDB album in list)
        {

            System.Diagnostics.Debug.WriteLine("list item: " + album.ID);

            System.Xml.XmlAttribute xmlId = doc.CreateAttribute("Id");
            xmlId.Value = album.ID.ToString();

            System.Xml.XmlAttribute xmlName = doc.CreateAttribute("name");
            xmlName.Value = album.Name;

            System.Xml.XmlAttribute xmlUser = doc.CreateAttribute("user");
            xmlUser.Value = album.User.ToString();

            System.Xml.XmlAttribute xmlPhoto = doc.CreateAttribute("photo");
            xmlPhoto.Value = getPhotoFromAlbum(album.ID);


            System.Xml.XmlNode xmlNode = doc.CreateNode(System.Xml.XmlNodeType.Element, "Album", "");
            xmlNode.Attributes.Append(xmlId);
            xmlNode.Attributes.Append(xmlName);
            xmlNode.Attributes.Append(xmlUser);
            xmlNode.Attributes.Append(xmlPhoto);
            rootNode.AppendChild(xmlNode);
        }

        System.Diagnostics.Debug.WriteLine("file: " + doc.InnerXml);

        //System.Xml.XmlDocument xDoc = new System.Xml.XmlDocument();
        //xDoc.LoadXml(xml.Value);

        doc.Save(Server.MapPath("~/App_Data/tempAlbum.xml"));
        //XDSPhoto.Data = doc.InnerXml;
        XDSAlbums.DataFile = Server.MapPath("~/App_Data/tempAlbum.xml");
        XDSAlbums.DataBind();
        XDSAlbums.Save();
        //XDSMovie.Data
    }

    private List<Models.AlbumDB> getAlbums()
    {
        List<Models.AlbumDB> commentsList = new List<Models.AlbumDB>();

        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "select * from [dbo].[albums] where [user]=@id order by [Id] desc";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = userId;
            System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

            while (myReader.Read())
            {
                commentsList.Add(readerToAlbumDB(myReader));
                System.Diagnostics.Debug.WriteLine("getting item " + readerToAlbumDB(myReader).ID);
            }

            myReader.Close();
            con.Close();
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine(ex.ToString());
        }
        return commentsList;
    }

    private Models.AlbumDB readerToAlbumDB(System.Data.SqlClient.SqlDataReader myReader)
    {
        Models.AlbumDB album = new Models.AlbumDB();

        album.ID = int.Parse(myReader["Id"].ToString());
        album.Name = myReader["name"].ToString();
        album.User = int.Parse(myReader["user"].ToString());

        return album;
    }
    
    String getPhotoFromAlbum(int albumId)
    {
        String ext = "";
        String photo = "";

        List<Models.PhotoDB> photosList = new List<Models.PhotoDB>();

        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "select * from [dbo].[photos] where [album]=@id";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = albumId;
            System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

            if (myReader.Read())
            {
                ext = myReader["photoType"].ToString();
                //considering "photo's" bytes are on 2nd column
                byte[] photoBytes = (byte[])myReader.GetValue(2);

                string base64String = Convert.ToBase64String(photoBytes, 0, photoBytes.Length);
                photo = base64String;
            }

            myReader.Close();
            con.Close();
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine(ex.ToString());
        }
        if (ext != "" && photo != "")
        {
            return "data:image/" + ext + ";base64," + photo;
        }
        else
        {
            return "~/Assets/empty_image.jpg";
        }
    }

    void AddNewAlbumButton_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/Album.aspx?albumId=" + createNewAlbum().ToString());
    }
    
</script>
<body>
    <form id="form1" runat="server">
    
                    <div style="background-color: #cceeff; clear: left; width: auto; padding: 5px; margin:10px; display:inline-block">
                        <asp:Image ID="Img1" runat="server" ImageUrl="~/Assets/empty_image.jpg" Width="400" Height="300"/>
                        <asp:Button ID="AddNewAlbumButton" OnClick="AddNewAlbumButton_Click" runat="server" Text="New Album" style="float:right; margin-top:30%; margin-left:20px; margin-right:20px"/>
                    </div>
        </form>
    
    
        <asp:XmlDataSource ID="XDSAlbums" runat="server" XPath="Albums/Album"></asp:XmlDataSource>

        <asp:Repeater ID="Repeater1" runat="server" DataSourceID="XDSAlbums">
            <ItemTemplate>
                    <div style="background-color: #cceeff; clear: left; width: auto; padding: 5px; margin:10px; display:inline-block" DataSource='<%# XPathSelect("Album") %>'>
                        <!--<img runat="server" id="MovieImg" width="120" height="190" src='<%# "~/Images/" + XPath("@ID") + ".jpg" %>' />-->
                        <asp:Image ID="Img1" runat="server" ImageUrl='<%# XPath("@photo") %>' Width="400" Height="300"/>
                        <asp:HyperLink ID="HyperLink1" NavigateUrl='<%# "~/Album.aspx?albumId=" + XPath("@Id") %>' runat="server" style="float:right; margin-top:30%; margin-left:20px; margin-right:20px">'<%# XPath("@name") %>'</asp:HyperLink>
                    </div>
            </ItemTemplate>
            <SeparatorTemplate>
                <br />
            </SeparatorTemplate>
        </asp:Repeater>
</body>
</html>

</asp:Content>