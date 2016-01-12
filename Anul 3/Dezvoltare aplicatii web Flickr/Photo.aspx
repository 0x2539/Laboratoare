<%@ Page Language="C#" MasterPageFile="~/MasterPagePhoto.master" AutoEventWireup="true" CodeFile="Photo.aspx.cs" Inherits="Photo" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
    
<script runat="server">

    int currentId = -1;
    int userId;
    int ownerId;

    void Page_Load(object sender, EventArgs e)
    {
        int.TryParse(Request.QueryString["photoId"], out currentId);
        userId = getUserId();

        if (isPhotoValid())
        {
            /*
            if (!IsPostBack)
            {
                AlbumNameTextBox.Text = getAlbumName();
            }
            loadPhotos();*/
            loadComments();
        }
        else
        {
            System.Xml.XmlDocument doc = new System.Xml.XmlDocument();// XDSPhoto.GetXmlDocument();
            doc.LoadXml("<Comments></Comments>");

            doc.Save(Server.MapPath("~/App_Data/tempPhoto.xml"));
            //XDSPhoto.Data = doc.InnerXml;
            XDSComment.DataFile = Server.MapPath("~/App_Data/tempPhoto.xml");
            //XDSPhoto.Data = xDoc.InnerXml;
            XDSComment.DataBind();
            XDSComment.Save();
        }
        btnAddComment.DataBind();
        btnDeletePhoto.DataBind();
        commentTextArea.DataBind();
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

    Boolean isPhotoValid()
    {
        if (currentId > 0)
        {
            try
            {
                System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
                con.Open();
                string strQuery = "select * from [dbo].[photos] where [Id]=@id";
                System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
                cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = currentId;
                System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

                if (myReader.Read())
                {
                    // Assuming your desired value is the name as the 3rd field
                    Models.PhotoDB photo = readerToPhotoDB(myReader);
                    uploadedImage.ImageUrl = "data:image/" + photo.PhotoType + ";base64," + photo.Photo;
                    ownerId = photo.User;
                    
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
        }
        return false;
    }

    private Models.PhotoDB readerToPhotoDB(System.Data.SqlClient.SqlDataReader myReader)
    {
        Models.PhotoDB newPhoto = new Models.PhotoDB();

        newPhoto.ID = int.Parse(myReader["Id"].ToString());
        newPhoto.PhotoType = myReader["photoType"].ToString();
        newPhoto.Category = myReader["category"].ToString();
        newPhoto.Description = myReader["description"].ToString();
        newPhoto.User = int.Parse(myReader["user"].ToString());

        //considering "photo's" bytes are on 2nd column
        byte[] Photo = (byte[])myReader.GetValue(2);

        string base64String = Convert.ToBase64String(Photo, 0, Photo.Length);
        newPhoto.Photo = base64String;

        return newPhoto;
    }
    
    void loadComments()
    {
        System.Diagnostics.Debug.WriteLine("getting list");
        List<Models.CommentDB> list = getComments();
        System.Diagnostics.Debug.WriteLine("got list");

        System.Xml.XmlDocument doc = new System.Xml.XmlDocument();
        doc.LoadXml("<Comments></Comments>");
        System.Xml.XmlNode rootNode = doc.SelectSingleNode("Comments");

        System.Diagnostics.Debug.WriteLine("list size: " + list.Count);
        foreach (Models.CommentDB comment in list)
        {

            System.Diagnostics.Debug.WriteLine("list item: " + comment.ID);

            System.Xml.XmlAttribute xmlId = doc.CreateAttribute("Id");
            xmlId.Value = comment.ID.ToString();

            System.Xml.XmlAttribute xmlText = doc.CreateAttribute("text");
            xmlText.Value = comment.Text;

            System.Xml.XmlAttribute xmlPhoto = doc.CreateAttribute("photo");
            xmlPhoto.Value = comment.Photo.ToString();

            System.Xml.XmlAttribute xmlUser = doc.CreateAttribute("user");
            xmlUser.Value = comment.User.ToString();

            
            System.Xml.XmlNode xmlNode = doc.CreateNode(System.Xml.XmlNodeType.Element, "Comment", "");
            xmlNode.Attributes.Append(xmlId);
            xmlNode.Attributes.Append(xmlText);
            xmlNode.Attributes.Append(xmlPhoto);
            xmlNode.Attributes.Append(xmlUser);
            rootNode.AppendChild(xmlNode);
        }

        System.Diagnostics.Debug.WriteLine("file: " + doc.InnerXml);

        //System.Xml.XmlDocument xDoc = new System.Xml.XmlDocument();
        //xDoc.LoadXml(xml.Value);

        doc.Save(Server.MapPath("~/App_Data/tempPhoto.xml"));
        //XDSPhoto.Data = doc.InnerXml;
        XDSComment.DataFile = Server.MapPath("~/App_Data/tempPhoto.xml");
        XDSComment.DataBind();
        XDSComment.Save();
        //XDSMovie.Data
    }

    private List<Models.CommentDB> getComments()
    {
        List<Models.CommentDB> commentsList = new List<Models.CommentDB>();

        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "select * from [dbo].[comments] where [photo]=@id order by [Id] desc";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = currentId;
            System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

            while (myReader.Read())
            {
                commentsList.Add(readerToCommentDB(myReader));
                System.Diagnostics.Debug.WriteLine("getting item " + readerToCommentDB(myReader).ID);
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

    private Models.CommentDB readerToCommentDB(System.Data.SqlClient.SqlDataReader myReader)
    {
        Models.CommentDB comment = new Models.CommentDB();

        comment.ID = int.Parse(myReader["Id"].ToString());
        comment.Text = myReader["text"].ToString().Replace("\n", "<br/>");
        comment.Photo = int.Parse(myReader["photo"].ToString());
        comment.User = int.Parse(myReader["user"].ToString());

        return comment;
    }

    void btnAddComment_Click(object sender, EventArgs e)
    {
        insertComment();
        loadComments();
        commentTextArea.InnerText = "";
    }
    
    void insertComment()
    {
        if (commentTextArea.InnerText.Length > 0)
        {
            try
            {
                System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
                con.Open();
                //insert the file into database
                string strQuery = "insert into [dbo].[comments] ([text], [user], [photo]) values (@text, @user, @photo);SELECT CAST(scope_identity() AS int)";
                System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
                cmd.Parameters.Add("@text", System.Data.SqlDbType.VarChar).Value = commentTextArea.InnerText;
                cmd.Parameters.Add("@user", System.Data.SqlDbType.Int).Value = userId;
                cmd.Parameters.Add("@photo", System.Data.SqlDbType.Int).Value = currentId;
                cmd.ExecuteNonQuery();
                con.Close();
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

    string getUsernameById(string id)
    {
        try
        {
            System.Data.SqlClient.SqlConnection con = new System.Data.SqlClient.SqlConnection(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\Database.mdf;Integrated Security=True;");
            con.Open();
            string strQuery = "select [username] from [dbo].[users] where [Id]=@id order by [Id] desc";
            System.Data.SqlClient.SqlCommand cmd = new System.Data.SqlClient.SqlCommand(strQuery, con);
            cmd.Parameters.AddWithValue("@id", System.Data.SqlDbType.Int).Value = int.Parse(id);
            System.Data.SqlClient.SqlDataReader myReader = cmd.ExecuteReader();

            if (myReader.Read())
            {
                string name = myReader["username"].ToString();
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
    
    bool canDeleteComment(String commenterId)
    {
        int id = int.Parse(commenterId);
        //if the current user is the owner of the photo
        if(userId == ownerId)
        {
            return true;
        }
        //if the current user wrote the comment
        if(userId == id)
        {
            return true;
        }
        return false;
    }

    bool canDeletePhoto()
    {
        //if the current user is the owner of the photo
        if (userId == ownerId && isPhotoValid())
        {
            return true;
        }
        return false;
    }

    Boolean canAddComment()
    {
        //if the current user is the owner of the photo
        if (userId != -1 && isPhotoValid())
        {
            return true;
        }
        return false;
    }
    
    String meth()
    {
        return "ceva";
    }
    
</script>

<body>
    
            <asp:Image ID="uploadedImage" runat="server" ImageUrl="~/Assets/empty_image.jpg" Width="800" Height="600"/>
    
    <form id="form1" runat="server">
            <textarea id="commentTextArea" runat="server" Visible='<%# canAddComment() %>' name="message" rows="5" cols="100" ></textarea> <br/>
            <asp:Button ID="btnAddComment" runat="server" Visible='<%# canAddComment() %>' Text="Add Comment" style="margin:20px" OnClick="btnAddComment_Click" />
            <asp:Button ID="btnDeletePhoto" runat="server" Visible='<%# canDeletePhoto() && canAddComment() %>' Text="Delete Photo" style="margin:20px" OnClick="btnAddComment_Click" />
    </form>

        <asp:XmlDataSource ID="XDSComment" runat="server" XPath="Comments/Comment" EnableCaching="false"></asp:XmlDataSource>

        <asp:Repeater ID="Repeater1" runat="server" DataSourceID="XDSComment">
            <ItemTemplate>
                    <div style="display: inline-block; width: 800px; margin:10px" DataSource='<%# XPathSelect("Comment") %>'>
                        <asp:HyperLink ID="HyperLinkUser" NavigateUrl='<%# "~/MyProfile.aspx?userId=" + XPath("@Id") %>' runat="server" style="float:left; margin:10px"><%#getUsernameById(XPath("@user").ToString())%></asp:HyperLink>
                        <asp:HyperLink ID="HyperLink1" Visible='<%# canDeleteComment(XPath("@user").ToString()) %>' NavigateUrl='<%# "~/DeleteComment.aspx?commentId=" + XPath("@Id") %>' runat="server" style="float:right; margin:10px">Delete</asp:HyperLink>
                        <div style="background-color: #cceeff; width: auto; height:auto; padding: 25px"><%#XPath("@text")%></div>
                    </div>
            </ItemTemplate>
            <SeparatorTemplate>
                <br />
            </SeparatorTemplate>
        </asp:Repeater>
    
    
</body>
</html>
    
</asp:Content>